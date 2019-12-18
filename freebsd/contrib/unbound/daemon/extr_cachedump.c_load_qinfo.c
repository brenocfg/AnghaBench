#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct regional {int dummy; } ;
struct query_info {size_t qname_len; int /*<<< orphan*/ * qname; int /*<<< orphan*/ * local_alias; int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; } ;
typedef  int /*<<< orphan*/  rr ;

/* Variables and functions */
 int LDNS_RR_BUF_SIZE ; 
 int /*<<< orphan*/  log_warn (char*,...) ; 
 scalar_t__ regional_alloc_init (struct regional*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_get_errorstr_parse (int) ; 
 int sldns_str2wire_rr_question_buf (char*,int /*<<< orphan*/ *,size_t*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_wirerr_get_class (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  sldns_wirerr_get_type (int /*<<< orphan*/ *,size_t,size_t) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static char*
load_qinfo(char* str, struct query_info* qinfo, struct regional* region)
{
	/* s is part of the buf */
	char* s = str;
	uint8_t rr[LDNS_RR_BUF_SIZE];
	size_t rr_len = sizeof(rr), dname_len = 0;
	int status;

	/* skip three words */
	s = strchr(str, ' ');
	if(s) s = strchr(s+1, ' ');
	if(s) s = strchr(s+1, ' ');
	if(!s) {
		log_warn("error line too short, %s", str);
		return NULL;
	}
	s[0] = 0;
	s++;

	/* parse them */
	status = sldns_str2wire_rr_question_buf(str, rr, &rr_len, &dname_len,
		NULL, 0, NULL, 0);
	if(status != 0) {
		log_warn("error cannot parse: %s %s",
			sldns_get_errorstr_parse(status), str);
		return NULL;
	}
	qinfo->qtype = sldns_wirerr_get_type(rr, rr_len, dname_len);
	qinfo->qclass = sldns_wirerr_get_class(rr, rr_len, dname_len);
	qinfo->qname_len = dname_len;
	qinfo->qname = (uint8_t*)regional_alloc_init(region, rr, dname_len);
	qinfo->local_alias = NULL;
	if(!qinfo->qname) {
		log_warn("error out of memory");
		return NULL;
	}

	return s;
}