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
typedef  unsigned char ldns_key ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (scalar_t__) ; 
 int /*<<< orphan*/  LDNS_FREE (unsigned char*) ; 
 scalar_t__ ldns_key_evp_key (unsigned char*) ; 
 unsigned char* ldns_key_hmac_key (unsigned char*) ; 
 scalar_t__ ldns_key_pubkey_owner (unsigned char*) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (scalar_t__) ; 

void
ldns_key_deep_free(ldns_key *key)
{
	unsigned char* hmac;
	if (ldns_key_pubkey_owner(key)) {
		ldns_rdf_deep_free(ldns_key_pubkey_owner(key));
	}
#ifdef HAVE_SSL
	if (ldns_key_evp_key(key)) {
		EVP_PKEY_free(ldns_key_evp_key(key));
	}
#endif /* HAVE_SSL */
	if (ldns_key_hmac_key(key)) {
		hmac = ldns_key_hmac_key(key);
		LDNS_FREE(hmac);
	}
	LDNS_FREE(key);
}