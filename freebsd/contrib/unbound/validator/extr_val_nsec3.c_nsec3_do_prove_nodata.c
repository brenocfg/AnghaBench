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
struct ub_packed_rrset_key {int dummy; } ;
struct query_info {size_t qname_len; scalar_t__ qtype; int /*<<< orphan*/ * qname; } ;
struct nsec3_filter {int dummy; } ;
struct module_env {int /*<<< orphan*/  scratch; } ;
struct ce_response {int /*<<< orphan*/  nc_rr; scalar_t__ nc_rrset; int /*<<< orphan*/  ce_len; scalar_t__ ce; } ;
typedef  int /*<<< orphan*/  rbtree_type ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_CNAME ; 
 scalar_t__ LDNS_RR_TYPE_DS ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  dname_is_root (int /*<<< orphan*/ *) ; 
 scalar_t__ find_matching_nsec3 (struct module_env*,struct nsec3_filter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,struct ub_packed_rrset_key**,int*) ; 
 int /*<<< orphan*/  log_assert (scalar_t__) ; 
 int /*<<< orphan*/ * nsec3_ce_wildcard (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ nsec3_has_optout (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nsec3_has_type (struct ub_packed_rrset_key*,int,scalar_t__) ; 
 int nsec3_prove_closest_encloser (struct module_env*,struct nsec3_filter*,int /*<<< orphan*/ *,struct query_info*,int,struct ce_response*) ; 
 int sec_status_bogus ; 
 int sec_status_insecure ; 
 int sec_status_secure ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum sec_status
nsec3_do_prove_nodata(struct module_env* env, struct nsec3_filter* flt, 
	rbtree_type* ct, struct query_info* qinfo)
{
	struct ce_response ce;
	uint8_t* wc;
	size_t wclen;
	struct ub_packed_rrset_key* rrset;
	int rr;
	enum sec_status sec;

	if(find_matching_nsec3(env, flt, ct, qinfo->qname, qinfo->qname_len, 
		&rrset, &rr)) {
		/* cases 1 and 2 */
		if(nsec3_has_type(rrset, rr, qinfo->qtype)) {
			verbose(VERB_ALGO, "proveNodata: Matching NSEC3 "
				"proved that type existed, bogus");
			return sec_status_bogus;
		} else if(nsec3_has_type(rrset, rr, LDNS_RR_TYPE_CNAME)) {
			verbose(VERB_ALGO, "proveNodata: Matching NSEC3 "
				"proved that a CNAME existed, bogus");
			return sec_status_bogus;
		}

		/* 
		 * If type DS: filter_init zone find already found a parent
		 *   zone, so this nsec3 is from a parent zone. 
		 *   o can be not a delegation (unusual query for normal name,
		 *   	no DS anyway, but we can verify that).
		 *   o can be a delegation (which is the usual DS check).
		 *   o may not have the SOA bit set (only the top of the
		 *   	zone, which must have been above the name, has that).
		 *   	Except for the root; which is checked by itself.
		 *
		 * If not type DS: matching nsec3 must not be a delegation.
		 */
		if(qinfo->qtype == LDNS_RR_TYPE_DS && qinfo->qname_len != 1 
			&& nsec3_has_type(rrset, rr, LDNS_RR_TYPE_SOA) &&
			!dname_is_root(qinfo->qname)) {
			verbose(VERB_ALGO, "proveNodata: apex NSEC3 "
				"abused for no DS proof, bogus");
			return sec_status_bogus;
		} else if(qinfo->qtype != LDNS_RR_TYPE_DS && 
			nsec3_has_type(rrset, rr, LDNS_RR_TYPE_NS) &&
			!nsec3_has_type(rrset, rr, LDNS_RR_TYPE_SOA)) {
			if(!nsec3_has_type(rrset, rr, LDNS_RR_TYPE_DS)) {
				verbose(VERB_ALGO, "proveNodata: matching "
					"NSEC3 is insecure delegation");
				return sec_status_insecure;
			}
			verbose(VERB_ALGO, "proveNodata: matching "
				"NSEC3 is a delegation, bogus");
			return sec_status_bogus;
		}
		return sec_status_secure;
	}

	/* For cases 3 - 5, we need the proven closest encloser, and it 
	 * can't match qname. Although, at this point, we know that it 
	 * won't since we just checked that. */
	sec = nsec3_prove_closest_encloser(env, flt, ct, qinfo, 1, &ce);
	if(sec == sec_status_bogus) {
		verbose(VERB_ALGO, "proveNodata: did not match qname, "
		          "nor found a proven closest encloser.");
		return sec_status_bogus;
	} else if(sec==sec_status_insecure && qinfo->qtype!=LDNS_RR_TYPE_DS){
		verbose(VERB_ALGO, "proveNodata: closest nsec3 is insecure "
		          "delegation.");
		return sec_status_insecure;
	}

	/* Case 3: removed */

	/* Case 4: */
	log_assert(ce.ce);
	wc = nsec3_ce_wildcard(env->scratch, ce.ce, ce.ce_len, &wclen);
	if(wc && find_matching_nsec3(env, flt, ct, wc, wclen, &rrset, &rr)) {
		/* found wildcard */
		if(nsec3_has_type(rrset, rr, qinfo->qtype)) {
			verbose(VERB_ALGO, "nsec3 nodata proof: matching "
				"wildcard had qtype, bogus");
			return sec_status_bogus;
		} else if(nsec3_has_type(rrset, rr, LDNS_RR_TYPE_CNAME)) {
			verbose(VERB_ALGO, "nsec3 nodata proof: matching "
				"wildcard had a CNAME, bogus");
			return sec_status_bogus;
		}
		if(qinfo->qtype == LDNS_RR_TYPE_DS && qinfo->qname_len != 1 
			&& nsec3_has_type(rrset, rr, LDNS_RR_TYPE_SOA)) {
			verbose(VERB_ALGO, "nsec3 nodata proof: matching "
				"wildcard for no DS proof has a SOA, bogus");
			return sec_status_bogus;
		} else if(qinfo->qtype != LDNS_RR_TYPE_DS && 
			nsec3_has_type(rrset, rr, LDNS_RR_TYPE_NS) &&
			!nsec3_has_type(rrset, rr, LDNS_RR_TYPE_SOA)) {
			verbose(VERB_ALGO, "nsec3 nodata proof: matching "
				"wildcard is a delegation, bogus");
			return sec_status_bogus;
		}
		/* everything is peachy keen, except for optout spans */
		if(ce.nc_rrset && nsec3_has_optout(ce.nc_rrset, ce.nc_rr)) {
			verbose(VERB_ALGO, "nsec3 nodata proof: matching "
				"wildcard is in optout range, insecure");
			return sec_status_insecure;
		}
		return sec_status_secure;
	}

	/* Case 5: */
	/* Due to forwarders, cnames, and other collating effects, we
	 * can see the ordinary unsigned data from a zone beneath an
	 * insecure delegation under an optout here */
	if(!ce.nc_rrset) {
		verbose(VERB_ALGO, "nsec3 nodata proof: no next closer nsec3");
		return sec_status_bogus;
	}

	/* We need to make sure that the covering NSEC3 is opt-out. */
	log_assert(ce.nc_rrset);
	if(!nsec3_has_optout(ce.nc_rrset, ce.nc_rr)) {
		if(qinfo->qtype == LDNS_RR_TYPE_DS)
		  verbose(VERB_ALGO, "proveNodata: covering NSEC3 was not "
			"opt-out in an opt-out DS NOERROR/NODATA case.");
		else verbose(VERB_ALGO, "proveNodata: could not find matching "
			"NSEC3, nor matching wildcard, nor optout NSEC3 "
			"-- no more options, bogus.");
		return sec_status_bogus;
	}
	/* RFC5155 section 9.2: if nc has optout then no AD flag set */
	return sec_status_insecure;
}