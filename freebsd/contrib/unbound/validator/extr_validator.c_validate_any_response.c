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
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct reply_info {int security; size_t an_numrrsets; size_t ns_numrrsets; struct ub_packed_rrset_key** rrsets; } ;
struct query_info {scalar_t__ qtype; } ;
struct module_env {int dummy; } ;
struct key_entry_key {int dummy; } ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_ANY ; 
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int nsec3_prove_wildcard (struct module_env*,struct val_env*,struct ub_packed_rrset_key**,size_t,struct query_info*,struct key_entry_key*,int /*<<< orphan*/ *) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 void* sec_status_bogus ; 
 int sec_status_insecure ; 
 int sec_status_secure ; 
 scalar_t__ val_nsec_proves_positive_wildcard (struct ub_packed_rrset_key*,struct query_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  val_rrset_wildcard (struct ub_packed_rrset_key*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
validate_any_response(struct module_env* env, struct val_env* ve,
	struct query_info* qchase, struct reply_info* chase_reply,
	struct key_entry_key* kkey)
{
	/* all answer and auth rrsets already verified */
	/* but check if a wildcard response is given, then check NSEC/NSEC3
	 * for qname denial to see if wildcard is applicable */
	uint8_t* wc = NULL;
	size_t wl;
	int wc_NSEC_ok = 0;
	int nsec3s_seen = 0;
	size_t i;
	struct ub_packed_rrset_key* s;

	if(qchase->qtype != LDNS_RR_TYPE_ANY) {
		log_err("internal error: ANY validation called for non-ANY");
		chase_reply->security = sec_status_bogus;
		return;
	}

	/* validate the ANSWER section - this will be the answer itself */
	for(i=0; i<chase_reply->an_numrrsets; i++) {
		s = chase_reply->rrsets[i];

		/* Check to see if the rrset is the result of a wildcard 
		 * expansion. If so, an additional check will need to be 
		 * made in the authority section. */
		if(!val_rrset_wildcard(s, &wc, &wl)) {
			log_nametypeclass(VERB_QUERY, "Positive ANY response"
				" has inconsistent wildcard sigs:", 
				s->rk.dname, ntohs(s->rk.type), 
				ntohs(s->rk.rrset_class));
			chase_reply->security = sec_status_bogus;
			return;
		}
	}

	/* if it was a wildcard, check for NSEC/NSEC3s in both answer
	 * and authority sections (NSEC may be moved to the ANSWER section) */
	if(wc != NULL)
	  for(i=0; i<chase_reply->an_numrrsets+chase_reply->ns_numrrsets; 
	  	i++) {
		s = chase_reply->rrsets[i];

		/* If this is a positive wildcard response, and we have a 
		 * (just verified) NSEC record, try to use it to 1) prove 
		 * that qname doesn't exist and 2) that the correct wildcard 
		 * was used. */
		if(ntohs(s->rk.type) == LDNS_RR_TYPE_NSEC) {
			if(val_nsec_proves_positive_wildcard(s, qchase, wc)) {
				wc_NSEC_ok = 1;
			}
			/* if not, continue looking for proof */
		}

		/* Otherwise, if this is a positive wildcard response and 
		 * we have NSEC3 records */
		if(ntohs(s->rk.type) == LDNS_RR_TYPE_NSEC3) {
			nsec3s_seen = 1;
		}
	}

	/* If this was a positive wildcard response that we haven't already
	 * proven, and we have NSEC3 records, try to prove it using the NSEC3
	 * records. */
	if(wc != NULL && !wc_NSEC_ok && nsec3s_seen) {
		/* look both in answer and auth section for NSEC3s */
		enum sec_status sec = nsec3_prove_wildcard(env, ve, 
			chase_reply->rrsets,
			chase_reply->an_numrrsets+chase_reply->ns_numrrsets, 
			qchase, kkey, wc);
		if(sec == sec_status_insecure) {
			verbose(VERB_ALGO, "Positive ANY wildcard response is "
				"insecure");
			chase_reply->security = sec_status_insecure;
			return;
		} else if(sec == sec_status_secure)
			wc_NSEC_ok = 1;
	}

	/* If after all this, we still haven't proven the positive wildcard
	 * response, fail. */
	if(wc != NULL && !wc_NSEC_ok) {
		verbose(VERB_QUERY, "positive ANY response was wildcard "
			"expansion and did not prove original data "
			"did not exist");
		chase_reply->security = sec_status_bogus;
		return;
	}

	verbose(VERB_ALGO, "Successfully validated positive ANY response");
	chase_reply->security = sec_status_secure;
}