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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_dnssec_zone ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_dnssec_zone_create_nsec3s_mkmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ldns_status
ldns_dnssec_zone_create_nsec3s(ldns_dnssec_zone *zone,
		ldns_rr_list *new_rrs,
		uint8_t algorithm,
		uint8_t flags,
		uint16_t iterations,
		uint8_t salt_length,
		uint8_t *salt)
{
	return ldns_dnssec_zone_create_nsec3s_mkmap(zone, new_rrs, algorithm,
		       	flags, iterations, salt_length, salt, NULL);

}