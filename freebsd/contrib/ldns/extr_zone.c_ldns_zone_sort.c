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
typedef  int /*<<< orphan*/  ldns_zone ;
typedef  int /*<<< orphan*/  ldns_rr_list ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_sort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_zone_rrs (int /*<<< orphan*/ *) ; 

void
ldns_zone_sort(ldns_zone *zone)
{
	ldns_rr_list *zrr;
	assert(zone != NULL);

	zrr = ldns_zone_rrs(zone);
	ldns_rr_list_sort(zrr);
}