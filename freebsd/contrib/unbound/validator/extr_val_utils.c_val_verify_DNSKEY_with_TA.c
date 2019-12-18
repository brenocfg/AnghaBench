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
struct val_env {int dummy; } ;
struct TYPE_2__ {scalar_t__ dname_len; int /*<<< orphan*/  dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct module_qstate {int dummy; } ;
struct module_env {int dummy; } ;
struct algo_needs {int dummy; } ;
typedef  int /*<<< orphan*/  needs ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  algo_needs_init_dnskey_add (struct algo_needs*,struct ub_packed_rrset_key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  algo_needs_init_ds (struct algo_needs*,struct ub_packed_rrset_key*,int,int /*<<< orphan*/ *) ; 
 int algo_needs_missing (struct algo_needs*) ; 
 int /*<<< orphan*/  algo_needs_reason (struct module_env*,int,char**,char*) ; 
 int /*<<< orphan*/  algo_needs_set_bogus (struct algo_needs*,int /*<<< orphan*/ ) ; 
 scalar_t__ algo_needs_set_secure (struct algo_needs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnskey_algo_is_supported (struct ub_packed_rrset_key*,size_t) ; 
 scalar_t__ dnskey_get_algo (struct ub_packed_rrset_key*,size_t) ; 
 int dnskey_verify_rrset (struct module_env*,struct val_env*,struct ub_packed_rrset_key*,struct ub_packed_rrset_key*,size_t,char**,int /*<<< orphan*/ ,struct module_qstate*) ; 
 int /*<<< orphan*/  ds_digest_algo_is_supported (struct ub_packed_rrset_key*,size_t) ; 
 int ds_get_digest_algo (struct ub_packed_rrset_key*,size_t) ; 
 scalar_t__ ds_get_key_algo (struct ub_packed_rrset_key*,size_t) ; 
 int /*<<< orphan*/  ds_key_algo_is_supported (struct ub_packed_rrset_key*,size_t) ; 
 int /*<<< orphan*/  memset (struct algo_needs*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t rrset_get_count (struct ub_packed_rrset_key*) ; 
 int sec_status_bogus ; 
 int sec_status_insecure ; 
 int sec_status_secure ; 
 int val_favorite_ds_algo (struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 
 int verify_dnskeys_with_ds_rr (struct module_env*,struct val_env*,struct ub_packed_rrset_key*,struct ub_packed_rrset_key*,size_t,char**,struct module_qstate*) ; 

enum sec_status 
val_verify_DNSKEY_with_TA(struct module_env* env, struct val_env* ve,
	struct ub_packed_rrset_key* dnskey_rrset,
	struct ub_packed_rrset_key* ta_ds,
	struct ub_packed_rrset_key* ta_dnskey, uint8_t* sigalg, char** reason,
	struct module_qstate* qstate)
{
	/* as long as this is false, we can consider this anchor to be
	 * equivalent to no anchor. */
	int has_useful_ta = 0, digest_algo = 0, alg;
	struct algo_needs needs;
	size_t i, num;
	enum sec_status sec;

	if(ta_ds && (dnskey_rrset->rk.dname_len != ta_ds->rk.dname_len ||
		query_dname_compare(dnskey_rrset->rk.dname, ta_ds->rk.dname)
		!= 0)) {
		verbose(VERB_QUERY, "DNSKEY RRset did not match DS RRset "
			"by name");
		*reason = "DNSKEY RRset did not match DS RRset by name";
		return sec_status_bogus;
	}
	if(ta_dnskey && (dnskey_rrset->rk.dname_len != ta_dnskey->rk.dname_len
	     || query_dname_compare(dnskey_rrset->rk.dname, ta_dnskey->rk.dname)
		!= 0)) {
		verbose(VERB_QUERY, "DNSKEY RRset did not match anchor RRset "
			"by name");
		*reason = "DNSKEY RRset did not match anchor RRset by name";
		return sec_status_bogus;
	}

	if(ta_ds)
		digest_algo = val_favorite_ds_algo(ta_ds);
	if(sigalg) {
		if(ta_ds)
			algo_needs_init_ds(&needs, ta_ds, digest_algo, sigalg);
		else	memset(&needs, 0, sizeof(needs));
		if(ta_dnskey)
			algo_needs_init_dnskey_add(&needs, ta_dnskey, sigalg);
	}
	if(ta_ds) {
	    num = rrset_get_count(ta_ds);
	    for(i=0; i<num; i++) {
		/* Check to see if we can understand this DS. 
		 * And check it is the strongest digest */
		if(!ds_digest_algo_is_supported(ta_ds, i) ||
			!ds_key_algo_is_supported(ta_ds, i) ||
			ds_get_digest_algo(ta_ds, i) != digest_algo)
			continue;

		/* Once we see a single DS with a known digestID and 
		 * algorithm, we cannot return INSECURE (with a 
		 * "null" KeyEntry). */
		has_useful_ta = 1;

		sec = verify_dnskeys_with_ds_rr(env, ve, dnskey_rrset, 
			ta_ds, i, reason, qstate);
		if(sec == sec_status_secure) {
			if(!sigalg || algo_needs_set_secure(&needs,
				(uint8_t)ds_get_key_algo(ta_ds, i))) {
				verbose(VERB_ALGO, "DS matched DNSKEY.");
				return sec_status_secure;
			}
		} else if(sigalg && sec == sec_status_bogus) {
			algo_needs_set_bogus(&needs,
				(uint8_t)ds_get_key_algo(ta_ds, i));
		}
	    }
	}

	/* None of the DS's worked out: check the DNSKEYs. */
	if(ta_dnskey) {
	    num = rrset_get_count(ta_dnskey);
	    for(i=0; i<num; i++) {
		/* Check to see if we can understand this DNSKEY */
		if(!dnskey_algo_is_supported(ta_dnskey, i))
			continue;

		/* we saw a useful TA */
		has_useful_ta = 1;

		sec = dnskey_verify_rrset(env, ve, dnskey_rrset,
			ta_dnskey, i, reason, LDNS_SECTION_ANSWER, qstate);
		if(sec == sec_status_secure) {
			if(!sigalg || algo_needs_set_secure(&needs,
				(uint8_t)dnskey_get_algo(ta_dnskey, i))) {
				verbose(VERB_ALGO, "anchor matched DNSKEY.");
				return sec_status_secure;
			}
		} else if(sigalg && sec == sec_status_bogus) {
			algo_needs_set_bogus(&needs,
				(uint8_t)dnskey_get_algo(ta_dnskey, i));
		}
	    }
	}

	/* If no DSs were understandable, then this is OK. */
	if(!has_useful_ta) {
		verbose(VERB_ALGO, "No usable trust anchors were found -- "
			"treating as insecure.");
		return sec_status_insecure;
	}
	/* If any were understandable, then it is bad. */
	verbose(VERB_QUERY, "Failed to match any usable anchor to a DNSKEY.");
	if(sigalg && (alg=algo_needs_missing(&needs)) != 0) {
		algo_needs_reason(env, alg, reason, "missing verification of "
			"DNSKEY signature");
	}
	return sec_status_bogus;
}