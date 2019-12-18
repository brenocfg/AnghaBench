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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_key_list ;
typedef  int /*<<< orphan*/  ldns_key ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int LDNS_KEY_ZONE_KEY ; 
 int /*<<< orphan*/  LDNS_MAX_PACKETLEN ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_create_empty_rrsig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ldns_key_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_key_list_key (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_key_list_key_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_key_use (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr2canonical (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_list2buffer_wire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_new () ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_sort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_set_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_set_ttl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_ttl (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rrsig2buffer_wire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_sign_public_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ldns_rr_list *
ldns_sign_public(ldns_rr_list *rrset, ldns_key_list *keys)
{
	ldns_rr_list *signatures;
	ldns_rr_list *rrset_clone;
	ldns_rr *current_sig;
	ldns_rdf *b64rdf;
	ldns_key *current_key;
	size_t key_count;
	uint16_t i;
	ldns_buffer *sign_buf;
	ldns_rdf *new_owner;

	if (!rrset || ldns_rr_list_rr_count(rrset) < 1 || !keys) {
		return NULL;
	}

	new_owner = NULL;

	signatures = ldns_rr_list_new();

	/* prepare a signature and add all the know data
	 * prepare the rrset. Sign this together.  */
	rrset_clone = ldns_rr_list_clone(rrset);
	if (!rrset_clone) {
		return NULL;
	}

	/* make it canonical */
	for(i = 0; i < ldns_rr_list_rr_count(rrset_clone); i++) {
		ldns_rr_set_ttl(ldns_rr_list_rr(rrset_clone, i), 
			ldns_rr_ttl(ldns_rr_list_rr(rrset, 0)));
		ldns_rr2canonical(ldns_rr_list_rr(rrset_clone, i));
	}
	/* sort */
	ldns_rr_list_sort(rrset_clone);

	for (key_count = 0;
		key_count < ldns_key_list_key_count(keys);
		key_count++) {
		if (!ldns_key_use(ldns_key_list_key(keys, key_count))) {
			continue;
		}
		sign_buf = ldns_buffer_new(LDNS_MAX_PACKETLEN);
		if (!sign_buf) {
			ldns_rr_list_free(rrset_clone);
			ldns_rr_list_free(signatures);
			ldns_rdf_free(new_owner);
			return NULL;
		}
		b64rdf = NULL;

		current_key = ldns_key_list_key(keys, key_count);
		/* sign all RRs with keys that have ZSKbit, !SEPbit.
		   sign DNSKEY RRs with keys that have ZSKbit&SEPbit */
		if (ldns_key_flags(current_key) & LDNS_KEY_ZONE_KEY) {
			current_sig = ldns_create_empty_rrsig(rrset_clone,
			                                      current_key);

			/* right now, we have: a key, a semi-sig and an rrset. For
			 * which we can create the sig and base64 encode that and
			 * add that to the signature */

			if (ldns_rrsig2buffer_wire(sign_buf, current_sig)
			    != LDNS_STATUS_OK) {
				ldns_buffer_free(sign_buf);
				/* ERROR */
				ldns_rr_list_deep_free(rrset_clone);
				ldns_rr_free(current_sig);
				ldns_rr_list_deep_free(signatures);
				return NULL;
			}

			/* add the rrset in sign_buf */
			if (ldns_rr_list2buffer_wire(sign_buf, rrset_clone)
			    != LDNS_STATUS_OK) {
				ldns_buffer_free(sign_buf);
				ldns_rr_list_deep_free(rrset_clone);
				ldns_rr_free(current_sig);
				ldns_rr_list_deep_free(signatures);
				return NULL;
			}

			b64rdf = ldns_sign_public_buffer(sign_buf, current_key);

			if (!b64rdf) {
				/* signing went wrong */
				ldns_rr_list_deep_free(rrset_clone);
				ldns_rr_free(current_sig);
				ldns_rr_list_deep_free(signatures);
				return NULL;
			}

			ldns_rr_rrsig_set_sig(current_sig, b64rdf);

			/* push the signature to the signatures list */
			ldns_rr_list_push_rr(signatures, current_sig);
		}
		ldns_buffer_free(sign_buf); /* restart for the next key */
	}
	ldns_rr_list_deep_free(rrset_clone);

	return signatures;
}