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
struct query_info {int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct nsec3_filter {int dummy; } ;
struct module_env {int dummy; } ;
struct ce_response {int /*<<< orphan*/  nc_rr; int /*<<< orphan*/  nc_rrset; int /*<<< orphan*/  ce; int /*<<< orphan*/  ce_rr; int /*<<< orphan*/  ce_rrset; } ;
typedef  int /*<<< orphan*/  rbtree_type ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DNAME ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  find_covering_nsec3 (struct module_env*,struct nsec3_filter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ce_response*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next_closer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  nsec3_find_closest_encloser (struct module_env*,struct nsec3_filter*,int /*<<< orphan*/ *,struct query_info*,struct ce_response*) ; 
 scalar_t__ nsec3_has_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sec_status_bogus ; 
 int sec_status_insecure ; 
 int sec_status_secure ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum sec_status
nsec3_prove_closest_encloser(struct module_env* env, struct nsec3_filter* flt, 
	rbtree_type* ct, struct query_info* qinfo, int prove_does_not_exist,
	struct ce_response* ce)
{
	uint8_t* nc;
	size_t nc_len;
	/* robust: clean out ce, in case it gets abused later */
	memset(ce, 0, sizeof(*ce));

	if(!nsec3_find_closest_encloser(env, flt, ct, qinfo, ce)) {
		verbose(VERB_ALGO, "nsec3 proveClosestEncloser: could "
			"not find a candidate for the closest encloser.");
		return sec_status_bogus;
	}
	log_nametypeclass(VERB_ALGO, "ce candidate", ce->ce, 0, 0);

	if(query_dname_compare(ce->ce, qinfo->qname) == 0) {
		if(prove_does_not_exist) {
			verbose(VERB_ALGO, "nsec3 proveClosestEncloser: "
				"proved that qname existed, bad");
			return sec_status_bogus;
		}
		/* otherwise, we need to nothing else to prove that qname 
		 * is its own closest encloser. */
		return sec_status_secure;
	}

	/* If the closest encloser is actually a delegation, then the 
	 * response should have been a referral. If it is a DNAME, then 
	 * it should have been a DNAME response. */
	if(nsec3_has_type(ce->ce_rrset, ce->ce_rr, LDNS_RR_TYPE_NS) &&
		!nsec3_has_type(ce->ce_rrset, ce->ce_rr, LDNS_RR_TYPE_SOA)) {
		if(!nsec3_has_type(ce->ce_rrset, ce->ce_rr, LDNS_RR_TYPE_DS)) {
			verbose(VERB_ALGO, "nsec3 proveClosestEncloser: "
				"closest encloser is insecure delegation");
			return sec_status_insecure;
		}
		verbose(VERB_ALGO, "nsec3 proveClosestEncloser: closest "
			"encloser was a delegation, bad");
		return sec_status_bogus;
	}
	if(nsec3_has_type(ce->ce_rrset, ce->ce_rr, LDNS_RR_TYPE_DNAME)) {
		verbose(VERB_ALGO, "nsec3 proveClosestEncloser: closest "
			"encloser was a DNAME, bad");
		return sec_status_bogus;
	}
	
	/* Otherwise, we need to show that the next closer name is covered. */
	next_closer(qinfo->qname, qinfo->qname_len, ce->ce, &nc, &nc_len);
	if(!find_covering_nsec3(env, flt, ct, nc, nc_len, 
		&ce->nc_rrset, &ce->nc_rr)) {
		verbose(VERB_ALGO, "nsec3: Could not find proof that the "
		          "candidate encloser was the closest encloser");
		return sec_status_bogus;
	}
	return sec_status_secure;
}