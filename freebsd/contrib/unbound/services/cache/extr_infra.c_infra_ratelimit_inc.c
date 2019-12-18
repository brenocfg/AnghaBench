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
typedef  int /*<<< orphan*/  ts ;
typedef  int /*<<< orphan*/  time_t ;
struct sockaddr_storage {int dummy; } ;
struct query_info {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/ * qname; } ;
struct lruhash_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/  data; } ;
struct infra_cache {int dummy; } ;
struct comm_reply {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  ip ;
typedef  int /*<<< orphan*/  cs ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_OPS ; 
 int /*<<< orphan*/  addr_to_str (struct sockaddr_storage*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  infra_create_ratedata (struct infra_cache*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infra_dp_ratelimit ; 
 struct lruhash_entry* infra_find_ratedata (struct infra_cache*,int /*<<< orphan*/ *,size_t,int) ; 
 int infra_find_ratelimit (struct infra_cache*,int /*<<< orphan*/ *,size_t) ; 
 int* infra_rate_find_second (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int infra_rate_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_wire2str_class_buf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sldns_wire2str_type_buf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char*,int,char*,char*,char*,...) ; 

int infra_ratelimit_inc(struct infra_cache* infra, uint8_t* name,
	size_t namelen, time_t timenow, struct query_info* qinfo,
	struct comm_reply* replylist)
{
	int lim, max;
	struct lruhash_entry* entry;

	if(!infra_dp_ratelimit)
		return 1; /* not enabled */

	/* find ratelimit */
	lim = infra_find_ratelimit(infra, name, namelen);
	if(!lim)
		return 1; /* disabled for this domain */
	
	/* find or insert ratedata */
	entry = infra_find_ratedata(infra, name, namelen, 1);
	if(entry) {
		int premax = infra_rate_max(entry->data, timenow);
		int* cur = infra_rate_find_second(entry->data, timenow);
		(*cur)++;
		max = infra_rate_max(entry->data, timenow);
		lock_rw_unlock(&entry->lock);

		if(premax < lim && max >= lim) {
			char buf[257], qnm[257], ts[12], cs[12], ip[128];
			dname_str(name, buf);
			dname_str(qinfo->qname, qnm);
			sldns_wire2str_type_buf(qinfo->qtype, ts, sizeof(ts));
			sldns_wire2str_class_buf(qinfo->qclass, cs, sizeof(cs));
			ip[0]=0;
			if(replylist) {
				addr_to_str((struct sockaddr_storage *)&replylist->addr,
					replylist->addrlen, ip, sizeof(ip));
				verbose(VERB_OPS, "ratelimit exceeded %s %d query %s %s %s from %s", buf, lim, qnm, cs, ts, ip);
			} else {
				verbose(VERB_OPS, "ratelimit exceeded %s %d query %s %s %s", buf, lim, qnm, cs, ts);
			}
		}
		return (max < lim);
	}

	/* create */
	infra_create_ratedata(infra, name, namelen, timenow);
	return (1 < lim);
}