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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ldns_zone ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_key_list ;
typedef  int /*<<< orphan*/  ldns_dnssec_zone ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_dnssec_default_replace_signatures ; 
 int /*<<< orphan*/  ldns_dnssec_zone_add_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dnssec_zone_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_dnssec_zone_new () ; 
 int /*<<< orphan*/  ldns_dnssec_zone_sign_nsec3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_new () ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_zone_new () ; 
 int /*<<< orphan*/  ldns_zone_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_zone_rrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_zone_set_soa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_zone_soa (int /*<<< orphan*/ *) ; 

ldns_zone *
ldns_zone_sign_nsec3(ldns_zone *zone, ldns_key_list *key_list, uint8_t algorithm, uint8_t flags, uint16_t iterations, uint8_t salt_length, uint8_t *salt)
{
	ldns_dnssec_zone *dnssec_zone;
	ldns_zone *signed_zone;
	ldns_rr_list *new_rrs;
	size_t i;

	signed_zone = ldns_zone_new();
	dnssec_zone = ldns_dnssec_zone_new();

	(void) ldns_dnssec_zone_add_rr(dnssec_zone, ldns_zone_soa(zone));
	ldns_zone_set_soa(signed_zone, ldns_rr_clone(ldns_zone_soa(zone)));

	for (i = 0; i < ldns_rr_list_rr_count(ldns_zone_rrs(zone)); i++) {
		(void) ldns_dnssec_zone_add_rr(dnssec_zone,
								 ldns_rr_list_rr(ldns_zone_rrs(zone),
											  i));
		ldns_zone_push_rr(signed_zone, 
					   ldns_rr_clone(ldns_rr_list_rr(ldns_zone_rrs(zone),
											   i)));
	}

	new_rrs = ldns_rr_list_new();
	(void) ldns_dnssec_zone_sign_nsec3(dnssec_zone,
								new_rrs,
								key_list,
								ldns_dnssec_default_replace_signatures,
								NULL,
								algorithm,
								flags,
								iterations,
								salt_length,
								salt);

    	for (i = 0; i < ldns_rr_list_rr_count(new_rrs); i++) {
		ldns_rr_list_push_rr(ldns_zone_rrs(signed_zone),
						 ldns_rr_clone(ldns_rr_list_rr(new_rrs, i)));
	}

	ldns_rr_list_deep_free(new_rrs);
	ldns_dnssec_zone_free(dnssec_zone);

	return signed_zone;
}