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
typedef  int /*<<< orphan*/  uint8_t ;
struct sldns_file_parse_state {size_t prev_rr_len; int /*<<< orphan*/ * prev_rr; scalar_t__ origin_len; int /*<<< orphan*/ * origin; int /*<<< orphan*/  default_ttl; } ;
struct auth_zone {int dummy; } ;
struct auth_xfer {TYPE_2__* task_transfer; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  rr ;
struct TYPE_4__ {TYPE_1__* master; } ;
struct TYPE_3__ {int /*<<< orphan*/  file; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int LDNS_RR_BUF_SIZE ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERROR (int) ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_OFFSET (int) ; 
 int az_insert_rr (struct auth_zone*,int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_get_errorstr_parse (int /*<<< orphan*/ ) ; 
 int sldns_str2wire_rr_buf (char*,int /*<<< orphan*/ *,size_t*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
http_parse_add_rr(struct auth_xfer* xfr, struct auth_zone* z,
	sldns_buffer* buf, struct sldns_file_parse_state* pstate)
{
	uint8_t rr[LDNS_RR_BUF_SIZE];
	size_t rr_len, dname_len = 0;
	int e;
	char* line = (char*)sldns_buffer_begin(buf);
	rr_len = sizeof(rr);
	e = sldns_str2wire_rr_buf(line, rr, &rr_len, &dname_len,
		pstate->default_ttl,
		pstate->origin_len?pstate->origin:NULL, pstate->origin_len,
		pstate->prev_rr_len?pstate->prev_rr:NULL, pstate->prev_rr_len);
	if(e != 0) {
		log_err("%s/%s parse failure RR[%d]: %s in '%s'",
			xfr->task_transfer->master->host,
			xfr->task_transfer->master->file,
			LDNS_WIREPARSE_OFFSET(e),
			sldns_get_errorstr_parse(LDNS_WIREPARSE_ERROR(e)),
			line);
		return 0;
	}
	if(rr_len == 0)
		return 1; /* empty line or so */

	/* set prev */
	if(dname_len < sizeof(pstate->prev_rr)) {
		memmove(pstate->prev_rr, rr, dname_len);
		pstate->prev_rr_len = dname_len;
	}

	return az_insert_rr(z, rr, rr_len, dname_len, NULL);
}