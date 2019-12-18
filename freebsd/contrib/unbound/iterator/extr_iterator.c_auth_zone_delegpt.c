#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  qclass; } ;
struct module_qstate {int /*<<< orphan*/  region; scalar_t__ blacklist; TYPE_3__* env; TYPE_2__ qinfo; } ;
struct TYPE_5__ {size_t qname_len; int /*<<< orphan*/ * qname; } ;
struct iter_qstate {struct delegpt* dp; TYPE_1__ qchase; scalar_t__ auth_zone_avoid; } ;
struct delegpt {int auth_dp; int /*<<< orphan*/  namelabs; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct auth_zone {int /*<<< orphan*/  lock; int /*<<< orphan*/  namelabs; int /*<<< orphan*/  namelen; scalar_t__ fallback_enabled; int /*<<< orphan*/  name; scalar_t__ for_upstream; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {TYPE_4__* auth_zones; } ;

/* Variables and functions */
 scalar_t__ VERB_ALGO ; 
 struct auth_zone* auth_zones_find_zone (TYPE_4__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dname_subdomain_c (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regional_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ regional_alloc_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verbose (scalar_t__,char*,char*) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static int
auth_zone_delegpt(struct module_qstate* qstate, struct iter_qstate* iq,
	uint8_t* delname, size_t delnamelen)
{
	struct auth_zone* z;
	if(iq->auth_zone_avoid)
		return 1;
	if(!delname) {
		delname = iq->qchase.qname;
		delnamelen = iq->qchase.qname_len;
	}
	lock_rw_rdlock(&qstate->env->auth_zones->lock);
	z = auth_zones_find_zone(qstate->env->auth_zones, delname, delnamelen,
		qstate->qinfo.qclass);
	if(!z) {
		lock_rw_unlock(&qstate->env->auth_zones->lock);
		return 1;
	}
	lock_rw_rdlock(&z->lock);
	lock_rw_unlock(&qstate->env->auth_zones->lock);
	if(z->for_upstream) {
		if(iq->dp && query_dname_compare(z->name, iq->dp->name) == 0
			&& iq->dp->auth_dp && qstate->blacklist &&
			z->fallback_enabled) {
			/* cache is blacklisted and fallback, and we
			 * already have an auth_zone dp */
			if(verbosity>=VERB_ALGO) {
				char buf[255+1];
				dname_str(z->name, buf);
				verbose(VERB_ALGO, "auth_zone %s "
				  "fallback because cache blacklisted",
				  buf);
			}
			lock_rw_unlock(&z->lock);
			iq->dp = NULL;
			return 1;
		}
		if(iq->dp==NULL || dname_subdomain_c(z->name, iq->dp->name)) {
			struct delegpt* dp;
			if(qstate->blacklist && z->fallback_enabled) {
				/* cache is blacklisted because of a DNSSEC
				 * validation failure, and the zone allows
				 * fallback to the internet, query there. */
				if(verbosity>=VERB_ALGO) {
					char buf[255+1];
					dname_str(z->name, buf);
					verbose(VERB_ALGO, "auth_zone %s "
					  "fallback because cache blacklisted",
					  buf);
				}
				lock_rw_unlock(&z->lock);
				return 1;
			}
			dp = (struct delegpt*)regional_alloc_zero(
				qstate->region, sizeof(*dp));
			if(!dp) {
				log_err("alloc failure");
				if(z->fallback_enabled) {
					lock_rw_unlock(&z->lock);
					return 1; /* just fallback */
				}
				lock_rw_unlock(&z->lock);
				errinf(qstate, "malloc failure");
				return 0;
			}
			dp->name = regional_alloc_init(qstate->region,
				z->name, z->namelen);
			if(!dp->name) {
				log_err("alloc failure");
				if(z->fallback_enabled) {
					lock_rw_unlock(&z->lock);
					return 1; /* just fallback */
				}
				lock_rw_unlock(&z->lock);
				errinf(qstate, "malloc failure");
				return 0;
			}
			dp->namelen = z->namelen;
			dp->namelabs = z->namelabs;
			dp->auth_dp = 1;
			iq->dp = dp;
		}
	}

	lock_rw_unlock(&z->lock);
	return 1;
}