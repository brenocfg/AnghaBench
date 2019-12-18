#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  _rrs; } ;
typedef  TYPE_1__ ldns_zone ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_rr_list_free (int /*<<< orphan*/ ) ; 

void
ldns_zone_free(ldns_zone *zone) 
{
	ldns_rr_list_free(zone->_rrs);
	LDNS_FREE(zone);
}