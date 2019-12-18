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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_dnssec_zone ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_dnssec_zone_mark_and_get_glue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ldns_status
ldns_dnssec_zone_mark_glue(ldns_dnssec_zone *zone)
{
	return ldns_dnssec_zone_mark_and_get_glue(zone, NULL);
}