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
struct val_env {int dummy; } ;
struct ub_packed_rrset_key {int dummy; } ;
struct module_qstate {int dummy; } ;
struct module_env {int /*<<< orphan*/ * now; } ;
struct algo_needs {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_pkt_section ;
typedef  int /*<<< orphan*/  rbtree_type ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  algo_needs_init_list (struct algo_needs*,int /*<<< orphan*/ *) ; 
 int algo_needs_missing (struct algo_needs*) ; 
 scalar_t__ algo_needs_num_missing (struct algo_needs*) ; 
 int /*<<< orphan*/  algo_needs_reason (struct module_env*,int,char**,char*) ; 
 int /*<<< orphan*/  algo_needs_set_bogus (struct algo_needs*,int /*<<< orphan*/ ) ; 
 scalar_t__ algo_needs_set_secure (struct algo_needs*,int /*<<< orphan*/ ) ; 
 int dnskeyset_verify_rrset_sig (struct module_env*,struct val_env*,int /*<<< orphan*/ ,struct ub_packed_rrset_key*,struct ub_packed_rrset_key*,size_t,int /*<<< orphan*/ **,char**,int /*<<< orphan*/ ,struct module_qstate*) ; 
 scalar_t__ rrset_get_sig_algo (struct ub_packed_rrset_key*,size_t) ; 
 size_t rrset_get_sigcount (struct ub_packed_rrset_key*) ; 
 int sec_status_bogus ; 
 int sec_status_insecure ; 
 int sec_status_secure ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

enum sec_status 
dnskeyset_verify_rrset(struct module_env* env, struct val_env* ve,
	struct ub_packed_rrset_key* rrset, struct ub_packed_rrset_key* dnskey,
	uint8_t* sigalg, char** reason, sldns_pkt_section section, 
	struct module_qstate* qstate)
{
	enum sec_status sec;
	size_t i, num;
	rbtree_type* sortree = NULL;
	/* make sure that for all DNSKEY algorithms there are valid sigs */
	struct algo_needs needs;
	int alg;

	num = rrset_get_sigcount(rrset);
	if(num == 0) {
		verbose(VERB_QUERY, "rrset failed to verify due to a lack of "
			"signatures");
		*reason = "no signatures";
		return sec_status_bogus;
	}

	if(sigalg) {
		algo_needs_init_list(&needs, sigalg);
		if(algo_needs_num_missing(&needs) == 0) {
			verbose(VERB_QUERY, "zone has no known algorithms");
			*reason = "zone has no known algorithms";
			return sec_status_insecure;
		}
	}
	for(i=0; i<num; i++) {
		sec = dnskeyset_verify_rrset_sig(env, ve, *env->now, rrset, 
			dnskey, i, &sortree, reason, section, qstate);
		/* see which algorithm has been fixed up */
		if(sec == sec_status_secure) {
			if(!sigalg)
				return sec; /* done! */
			else if(algo_needs_set_secure(&needs,
				(uint8_t)rrset_get_sig_algo(rrset, i)))
				return sec; /* done! */
		} else if(sigalg && sec == sec_status_bogus) {
			algo_needs_set_bogus(&needs,
				(uint8_t)rrset_get_sig_algo(rrset, i));
		}
	}
	if(sigalg && (alg=algo_needs_missing(&needs)) != 0) {
		verbose(VERB_ALGO, "rrset failed to verify: "
			"no valid signatures for %d algorithms",
			(int)algo_needs_num_missing(&needs));
		algo_needs_reason(env, alg, reason, "no signatures");
	} else {
		verbose(VERB_ALGO, "rrset failed to verify: "
			"no valid signatures");
	}
	return sec_status_bogus;
}