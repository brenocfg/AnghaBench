#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_4__ {int flags; int nquestions; TYPE_1__** questions; } ;
struct server_request {int trans_id; int n_answer; int n_authority; int n_additional; int response_len; unsigned char* response; struct server_reply_item* additional; struct server_reply_item* authority; struct server_reply_item* answer; TYPE_2__ base; } ;
struct server_reply_item {char const* name; int type; int dns_question_class; char const* data; int datalen; struct server_reply_item* next; scalar_t__ is_name; int /*<<< orphan*/  ttl; } ;
struct dnslabel_table {int dummy; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {char* name; int type; int dns_question_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND16 (int) ; 
 int /*<<< orphan*/  APPEND32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnslabel_clear (struct dnslabel_table*) ; 
 int /*<<< orphan*/  dnslabel_table_init (struct dnslabel_table*) ; 
 int dnsname_to_labels (unsigned char*,size_t,int,char const*,int /*<<< orphan*/ ,struct dnslabel_table*) ; 
 int htons (short) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,...) ; 
 unsigned char* mm_malloc (int) ; 
 int /*<<< orphan*/  server_request_free_answers (struct server_request*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
evdns_server_request_format_response(struct server_request *req, int err)
{
	unsigned char buf[1500];
	size_t buf_len = sizeof(buf);
	off_t j = 0, r;
	u16 t_;
	u32 t32_;
	int i;
	u16 flags;
	struct dnslabel_table table;

	if (err < 0 || err > 15) return -1;

	/* Set response bit and error code; copy OPCODE and RD fields from
	 * question; copy RA and AA if set by caller. */
	flags = req->base.flags;
	flags |= (0x8000 | err);

	dnslabel_table_init(&table);
	APPEND16(req->trans_id);
	APPEND16(flags);
	APPEND16(req->base.nquestions);
	APPEND16(req->n_answer);
	APPEND16(req->n_authority);
	APPEND16(req->n_additional);

	/* Add questions. */
	for (i=0; i < req->base.nquestions; ++i) {
		const char *s = req->base.questions[i]->name;
		j = dnsname_to_labels(buf, buf_len, j, s, strlen(s), &table);
		if (j < 0) {
			dnslabel_clear(&table);
			return (int) j;
		}
		APPEND16(req->base.questions[i]->type);
		APPEND16(req->base.questions[i]->dns_question_class);
	}

	/* Add answer, authority, and additional sections. */
	for (i=0; i<3; ++i) {
		struct server_reply_item *item;
		if (i==0)
			item = req->answer;
		else if (i==1)
			item = req->authority;
		else
			item = req->additional;
		while (item) {
			r = dnsname_to_labels(buf, buf_len, j, item->name, strlen(item->name), &table);
			if (r < 0)
				goto overflow;
			j = r;

			APPEND16(item->type);
			APPEND16(item->dns_question_class);
			APPEND32(item->ttl);
			if (item->is_name) {
				off_t len_idx = j, name_start;
				j += 2;
				name_start = j;
				r = dnsname_to_labels(buf, buf_len, j, item->data, strlen(item->data), &table);
				if (r < 0)
					goto overflow;
				j = r;
				t_ = htons( (short) (j-name_start) );
				memcpy(buf+len_idx, &t_, 2);
			} else {
				APPEND16(item->datalen);
				if (j+item->datalen > (off_t)buf_len)
					goto overflow;
				memcpy(buf+j, item->data, item->datalen);
				j += item->datalen;
			}
			item = item->next;
		}
	}

	if (j > 512) {
overflow:
		j = 512;
		buf[2] |= 0x02; /* set the truncated bit. */
	}

	req->response_len = j;

	if (!(req->response = mm_malloc(req->response_len))) {
		server_request_free_answers(req);
		dnslabel_clear(&table);
		return (-1);
	}
	memcpy(req->response, buf, req->response_len);
	server_request_free_answers(req);
	dnslabel_clear(&table);
	return (0);
}