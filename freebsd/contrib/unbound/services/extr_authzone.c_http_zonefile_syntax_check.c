#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct sldns_file_parse_state {int default_ttl; int origin_len; scalar_t__ prev_rr_len; int /*<<< orphan*/ * prev_rr; int /*<<< orphan*/ * origin; } ;
struct auth_xfer {int namelen; scalar_t__ dclass; TYPE_1__* task_transfer; int /*<<< orphan*/  name; } ;
struct auth_chunk {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  rr ;
typedef  int /*<<< orphan*/  pstate ;
struct TYPE_2__ {struct auth_chunk* chunks_first; } ;

/* Variables and functions */
 int LDNS_RR_BUF_SIZE ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERROR (int) ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_OFFSET (int) ; 
 int /*<<< orphan*/  chunkline_non_comment_RR (struct auth_chunk**,size_t*,int /*<<< orphan*/ *,struct sldns_file_parse_state*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sldns_file_parse_state*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_get_errorstr_parse (int /*<<< orphan*/ ) ; 
 int sldns_str2wire_rr_buf (char*,int /*<<< orphan*/ *,size_t*,size_t*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sldns_wirerr_get_class (int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static int
http_zonefile_syntax_check(struct auth_xfer* xfr, sldns_buffer* buf)
{
	uint8_t rr[LDNS_RR_BUF_SIZE];
	size_t rr_len, dname_len = 0;
	struct sldns_file_parse_state pstate;
	struct auth_chunk* chunk;
	size_t chunk_pos;
	int e;
	memset(&pstate, 0, sizeof(pstate));
	pstate.default_ttl = 3600;
	if(xfr->namelen < sizeof(pstate.origin)) {
		pstate.origin_len = xfr->namelen;
		memmove(pstate.origin, xfr->name, xfr->namelen);
	}
	chunk = xfr->task_transfer->chunks_first;
	chunk_pos = 0;
	if(!chunkline_non_comment_RR(&chunk, &chunk_pos, buf, &pstate)) {
		return 0;
	}
	rr_len = sizeof(rr);
	e=sldns_str2wire_rr_buf((char*)sldns_buffer_begin(buf), rr, &rr_len,
		&dname_len, pstate.default_ttl,
		pstate.origin_len?pstate.origin:NULL, pstate.origin_len,
		pstate.prev_rr_len?pstate.prev_rr:NULL, pstate.prev_rr_len);
	if(e != 0) {
		log_err("parse failure on first RR[%d]: %s",
			LDNS_WIREPARSE_OFFSET(e),
			sldns_get_errorstr_parse(LDNS_WIREPARSE_ERROR(e)));
		return 0;
	}
	/* check that class is correct */
	if(sldns_wirerr_get_class(rr, rr_len, dname_len) != xfr->dclass) {
		log_err("parse failure: first record in downloaded zonefile "
			"from wrong RR class");
		return 0;
	}
	return 1;
}