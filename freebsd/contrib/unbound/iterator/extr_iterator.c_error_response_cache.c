#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct reply_info {scalar_t__ serve_expired_ttl; int qdcount; int /*<<< orphan*/  security; scalar_t__ ttl; int /*<<< orphan*/  prefetch_ttl; scalar_t__ flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; scalar_t__ data; } ;
struct msgreply_entry {TYPE_2__ entry; } ;
struct TYPE_11__ {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct module_qstate {scalar_t__ prefetch_leeway; int /*<<< orphan*/  query_flags; TYPE_5__ qinfo; TYPE_3__* env; int /*<<< orphan*/  no_cache_store; } ;
typedef  int /*<<< orphan*/  err ;
struct TYPE_10__ {scalar_t__* now; TYPE_1__* cfg; } ;
struct TYPE_8__ {scalar_t__ serve_expired_ttl; scalar_t__ serve_expired_ttl_reset; scalar_t__ serve_expired; } ;

/* Variables and functions */
 int BIT_QR ; 
 int BIT_RA ; 
 scalar_t__ FLAGS_GET_RCODE (scalar_t__) ; 
 int /*<<< orphan*/  FLAGS_SET_RCODE (scalar_t__,int) ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_NXDOMAIN ; 
 scalar_t__ NORR_TTL ; 
 int /*<<< orphan*/  PREFETCH_TTL_CALC (scalar_t__) ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ dns_cache_prefetch_adjust (TYPE_3__*,TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int error_response (struct module_qstate*,int,int) ; 
 int /*<<< orphan*/  iter_dns_store (TYPE_3__*,TYPE_5__*,struct reply_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct reply_info*,int /*<<< orphan*/ ,int) ; 
 struct msgreply_entry* msg_cache_lookup (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sec_status_indeterminate ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
error_response_cache(struct module_qstate* qstate, int id, int rcode)
{
	if(!qstate->no_cache_store) {
		/* store in cache */
		struct reply_info err;
		if(qstate->prefetch_leeway > NORR_TTL) {
			verbose(VERB_ALGO, "error response for prefetch in cache");
			/* attempt to adjust the cache entry prefetch */
			if(dns_cache_prefetch_adjust(qstate->env, &qstate->qinfo,
				NORR_TTL, qstate->query_flags))
				return error_response(qstate, id, rcode);
			/* if that fails (not in cache), fall through to store err */
		}
		if(qstate->env->cfg->serve_expired) {
			/* if serving expired contents, and such content is
			 * already available, don't overwrite this servfail */
			struct msgreply_entry* msg;
			if((msg=msg_cache_lookup(qstate->env,
				qstate->qinfo.qname, qstate->qinfo.qname_len,
				qstate->qinfo.qtype, qstate->qinfo.qclass,
				qstate->query_flags, 0,
				qstate->env->cfg->serve_expired_ttl_reset))
				!= NULL) {
				if(qstate->env->cfg->serve_expired_ttl_reset) {
					struct reply_info* rep =
						(struct reply_info*)msg->entry.data;
					if(rep && *qstate->env->now +
						qstate->env->cfg->serve_expired_ttl  >
						rep->serve_expired_ttl) {
						rep->serve_expired_ttl =
							*qstate->env->now +
							qstate->env->cfg->serve_expired_ttl;
					}
				}
				lock_rw_unlock(&msg->entry.lock);
				return error_response(qstate, id, rcode);
			}
			/* serving expired contents, but nothing is cached
			 * at all, so the servfail cache entry is useful
			 * (stops waste of time on this servfail NORR_TTL) */
		} else {
			/* don't overwrite existing (non-expired) data in
			 * cache with a servfail */
			struct msgreply_entry* msg;
			if((msg=msg_cache_lookup(qstate->env,
				qstate->qinfo.qname, qstate->qinfo.qname_len,
				qstate->qinfo.qtype, qstate->qinfo.qclass,
				qstate->query_flags, *qstate->env->now, 0))
				!= NULL) {
				struct reply_info* rep = (struct reply_info*)
					msg->entry.data;
				if(FLAGS_GET_RCODE(rep->flags) ==
					LDNS_RCODE_NOERROR ||
					FLAGS_GET_RCODE(rep->flags) ==
					LDNS_RCODE_NXDOMAIN) {
					/* we have a good entry,
					 * don't overwrite */
					lock_rw_unlock(&msg->entry.lock);
					return error_response(qstate, id, rcode);
				}
				lock_rw_unlock(&msg->entry.lock);
			}
			
		}
		memset(&err, 0, sizeof(err));
		err.flags = (uint16_t)(BIT_QR | BIT_RA);
		FLAGS_SET_RCODE(err.flags, rcode);
		err.qdcount = 1;
		err.ttl = NORR_TTL;
		err.prefetch_ttl = PREFETCH_TTL_CALC(err.ttl);
		err.serve_expired_ttl = NORR_TTL;
		/* do not waste time trying to validate this servfail */
		err.security = sec_status_indeterminate;
		verbose(VERB_ALGO, "store error response in message cache");
		iter_dns_store(qstate->env, &qstate->qinfo, &err, 0, 0, 0, NULL,
			qstate->query_flags);
	}
	return error_response(qstate, id, rcode);
}