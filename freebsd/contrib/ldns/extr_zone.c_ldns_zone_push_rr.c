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
typedef  int /*<<< orphan*/  ldns_rr ;

/* Variables and functions */
 int ldns_rr_list_push_rr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_zone_rrs (int /*<<< orphan*/ *) ; 

bool
ldns_zone_push_rr(ldns_zone *z, ldns_rr *rr)
{
	return ldns_rr_list_push_rr(ldns_zone_rrs(z), rr);
}