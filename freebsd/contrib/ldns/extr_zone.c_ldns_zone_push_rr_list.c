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
 int ldns_rr_list_cat (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_zone_rrs (int /*<<< orphan*/ *) ; 

bool
ldns_zone_push_rr_list(ldns_zone *z, const ldns_rr_list *list)
{
	return ldns_rr_list_cat(ldns_zone_rrs(z), list);
}