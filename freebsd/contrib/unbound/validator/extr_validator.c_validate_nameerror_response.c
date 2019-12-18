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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct reply_info {size_t an_numrrsets; size_t ns_numrrsets; scalar_t__ security; struct ub_packed_rrset_key** rrsets; } ;
struct query_info {int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct module_env {int dummy; } ;
struct key_entry_key {int dummy; } ;

/* Variables and functions */
 int LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 scalar_t__ nsec3_prove_nameerror (struct module_env*,struct val_env*,struct ub_packed_rrset_key**,size_t,struct query_info*,struct key_entry_key*) ; 
 int /*<<< orphan*/ * nsec_closest_encloser (int /*<<< orphan*/ ,struct ub_packed_rrset_key*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 void* sec_status_bogus ; 
 scalar_t__ sec_status_insecure ; 
 scalar_t__ sec_status_secure ; 
 int /*<<< orphan*/  sec_status_to_string (scalar_t__) ; 
 scalar_t__ val_nsec_proves_insecuredelegation (struct ub_packed_rrset_key*,struct query_info*) ; 
 scalar_t__ val_nsec_proves_name_error (struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 scalar_t__ val_nsec_proves_no_wc (struct ub_packed_rrset_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_nodata_response (struct module_env*,struct val_env*,struct query_info*,struct reply_info*,struct key_entry_key*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
validate_nameerror_response(struct module_env* env, struct val_env* ve,
	struct query_info* qchase, struct reply_info* chase_reply,
	struct key_entry_key* kkey, int* rcode)
{
	int has_valid_nsec = 0;
	int has_valid_wnsec = 0;
	int nsec3s_seen = 0;
	struct ub_packed_rrset_key* s; 
	size_t i;
	uint8_t* ce;
	int ce_labs = 0;
	int prev_ce_labs = 0;

	for(i=chase_reply->an_numrrsets; i<chase_reply->an_numrrsets+
		chase_reply->ns_numrrsets; i++) {
		s = chase_reply->rrsets[i];
		if(ntohs(s->rk.type) == LDNS_RR_TYPE_NSEC) {
			if(val_nsec_proves_name_error(s, qchase->qname))
				has_valid_nsec = 1;
			ce = nsec_closest_encloser(qchase->qname, s);            
			ce_labs = dname_count_labels(ce);                        
			/* Use longest closest encloser to prove wildcard. */
			if(ce_labs > prev_ce_labs ||                             
			       (ce_labs == prev_ce_labs &&                      
				       has_valid_wnsec == 0)) {                 
			       if(val_nsec_proves_no_wc(s, qchase->qname,       
				       qchase->qname_len))                      
				       has_valid_wnsec = 1;                     
			       else                                             
				       has_valid_wnsec = 0;                     
			}                                                        
			prev_ce_labs = ce_labs; 
			if(val_nsec_proves_insecuredelegation(s, qchase)) {
				verbose(VERB_ALGO, "delegation is insecure");
				chase_reply->security = sec_status_insecure;
				return;
			}
		} else if(ntohs(s->rk.type) == LDNS_RR_TYPE_NSEC3)
			nsec3s_seen = 1;
	}

	if((!has_valid_nsec || !has_valid_wnsec) && nsec3s_seen) {
		/* use NSEC3 proof, both answer and auth rrsets, in case
		 * NSEC3s end up in the answer (due to qtype=NSEC3 or so) */
		chase_reply->security = nsec3_prove_nameerror(env, ve,
			chase_reply->rrsets, chase_reply->an_numrrsets+
			chase_reply->ns_numrrsets, qchase, kkey);
		if(chase_reply->security != sec_status_secure) {
			verbose(VERB_QUERY, "NameError response failed nsec, "
				"nsec3 proof was %s", sec_status_to_string(
				chase_reply->security));
			return;
		}
		has_valid_nsec = 1;
		has_valid_wnsec = 1;
	}

	/* If the message fails to prove either condition, it is bogus. */
	if(!has_valid_nsec) {
		verbose(VERB_QUERY, "NameError response has failed to prove: "
		          "qname does not exist");
		chase_reply->security = sec_status_bogus;
		/* Be lenient with RCODE in NSEC NameError responses */
		validate_nodata_response(env, ve, qchase, chase_reply, kkey);
		if (chase_reply->security == sec_status_secure)
			*rcode = LDNS_RCODE_NOERROR;
		return;
	}

	if(!has_valid_wnsec) {
		verbose(VERB_QUERY, "NameError response has failed to prove: "
		          "covering wildcard does not exist");
		chase_reply->security = sec_status_bogus;
		/* Be lenient with RCODE in NSEC NameError responses */
		validate_nodata_response(env, ve, qchase, chase_reply, kkey);
		if (chase_reply->security == sec_status_secure)
			*rcode = LDNS_RCODE_NOERROR;
		return;
	}

	/* Otherwise, we consider the message secure. */
	verbose(VERB_ALGO, "successfully validated NAME ERROR response.");
	chase_reply->security = sec_status_secure;
}