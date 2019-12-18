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
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int lineno; int /*<<< orphan*/  sin6_addr; void* sin6_port; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr_in {int lineno; int /*<<< orphan*/  sin6_addr; void* sin6_port; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sldns_file_parse_state {int lineno; int /*<<< orphan*/  sin6_addr; void* sin6_port; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct iter_hints {int dummy; } ;
struct delegpt {int has_parent_side_NS; int /*<<< orphan*/  name; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  rr ;
typedef  int /*<<< orphan*/  pstate ;
typedef  void* in_port_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ INET6_SIZE ; 
 scalar_t__ INET_SIZE ; 
 int LDNS_RR_BUF_SIZE ; 
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_OFFSET (int) ; 
 int /*<<< orphan*/  UNBOUND_DNS_PORT ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  delegpt_add_ns_mlc (struct delegpt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delegpt_add_target_mlc (struct delegpt*,int /*<<< orphan*/ *,size_t,struct sockaddr_storage*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct delegpt* delegpt_create_mlc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delegpt_free_mlc (struct delegpt*) ; 
 int /*<<< orphan*/  delegpt_log (int /*<<< orphan*/ ,struct delegpt*) ; 
 int /*<<< orphan*/  delegpt_set_name_mlc (struct delegpt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  hints_insert (struct iter_hints*,int /*<<< orphan*/ ,struct delegpt*,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  log_warn (char*,char*,...) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int sldns_fp2wire_rr_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,size_t*,struct sockaddr_in6*) ; 
 int /*<<< orphan*/  sldns_get_errorstr_parse (int) ; 
 int /*<<< orphan*/  sldns_wire2str_type_buf (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  sldns_wirerr_get_class (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  sldns_wirerr_get_rdata (int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ sldns_wirerr_get_rdatalen (int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ sldns_wirerr_get_type (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int 
read_root_hints(struct iter_hints* hints, char* fname)
{
	struct sldns_file_parse_state pstate;
	struct delegpt* dp;
	uint8_t rr[LDNS_RR_BUF_SIZE];
	size_t rr_len, dname_len;
	int status;
	uint16_t c = LDNS_RR_CLASS_IN;
	FILE* f = fopen(fname, "r");
	if(!f) {
		log_err("could not read root hints %s: %s",
			fname, strerror(errno));
		return 0;
	}
	dp = delegpt_create_mlc(NULL);
	if(!dp) {
		log_err("out of memory reading root hints");
		fclose(f);
		return 0;
	}
	verbose(VERB_QUERY, "Reading root hints from %s", fname);
	memset(&pstate, 0, sizeof(pstate));
	pstate.lineno = 1;
	dp->has_parent_side_NS = 1;
	while(!feof(f)) {
		rr_len = sizeof(rr);
		dname_len = 0;
		status = sldns_fp2wire_rr_buf(f, rr, &rr_len, &dname_len,
			&pstate);
		if(status != 0) {
			log_err("reading root hints %s %d:%d: %s", fname,
				pstate.lineno, LDNS_WIREPARSE_OFFSET(status),
				sldns_get_errorstr_parse(status));
			goto stop_read;
		}
		if(rr_len == 0)
			continue; /* EMPTY line, TTL or ORIGIN */
		if(sldns_wirerr_get_type(rr, rr_len, dname_len)
			== LDNS_RR_TYPE_NS) {
			if(!delegpt_add_ns_mlc(dp, sldns_wirerr_get_rdata(rr,
				rr_len, dname_len), 0)) {
				log_err("out of memory reading root hints");
				goto stop_read;
			}
			c = sldns_wirerr_get_class(rr, rr_len, dname_len);
			if(!dp->name) {
				if(!delegpt_set_name_mlc(dp, rr)) {
					log_err("out of memory.");
					goto stop_read;
				}
			}
		} else if(sldns_wirerr_get_type(rr, rr_len, dname_len)
			== LDNS_RR_TYPE_A && sldns_wirerr_get_rdatalen(rr,
			rr_len, dname_len) == INET_SIZE) {
			struct sockaddr_in sa;
			socklen_t len = (socklen_t)sizeof(sa);
			memset(&sa, 0, len);
			sa.sin_family = AF_INET;
			sa.sin_port = (in_port_t)htons(UNBOUND_DNS_PORT);
			memmove(&sa.sin_addr, 
				sldns_wirerr_get_rdata(rr, rr_len, dname_len),
				INET_SIZE);
			if(!delegpt_add_target_mlc(dp, rr, dname_len,
					(struct sockaddr_storage*)&sa, len, 
					0, 0)) {
				log_err("out of memory reading root hints");
				goto stop_read;
			}
		} else if(sldns_wirerr_get_type(rr, rr_len, dname_len)
			== LDNS_RR_TYPE_AAAA && sldns_wirerr_get_rdatalen(rr,
			rr_len, dname_len) == INET6_SIZE) {
			struct sockaddr_in6 sa;
			socklen_t len = (socklen_t)sizeof(sa);
			memset(&sa, 0, len);
			sa.sin6_family = AF_INET6;
			sa.sin6_port = (in_port_t)htons(UNBOUND_DNS_PORT);
			memmove(&sa.sin6_addr, 
				sldns_wirerr_get_rdata(rr, rr_len, dname_len),
				INET6_SIZE);
			if(!delegpt_add_target_mlc(dp, rr, dname_len,
					(struct sockaddr_storage*)&sa, len,
					0, 0)) {
				log_err("out of memory reading root hints");
				goto stop_read;
			}
		} else {
			char buf[17];
			sldns_wire2str_type_buf(sldns_wirerr_get_type(rr,
				rr_len, dname_len), buf, sizeof(buf));
			log_warn("root hints %s:%d skipping type %s",
				fname, pstate.lineno, buf);
		}
	}
	fclose(f);
	if(!dp->name) {
		log_warn("root hints %s: no NS content", fname);
		delegpt_free_mlc(dp);
		return 1;
	}
	if(!hints_insert(hints, c, dp, 0)) {
		return 0;
	}
	delegpt_log(VERB_QUERY, dp);
	return 1;

stop_read:
	delegpt_free_mlc(dp);
	fclose(f);
	return 0;
}