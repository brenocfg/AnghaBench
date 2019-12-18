#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* names; } ;
typedef  TYPE_1__ ldns_dnssec_zone ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_dnssec_name_node_free ; 
 int /*<<< orphan*/  ldns_traverse_postorder (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ldns_dnssec_zone_free(ldns_dnssec_zone *zone)
{
	if (zone) {
		if (zone->names) {
			/* destroy all name structures within the tree */
			ldns_traverse_postorder(zone->names,
						    ldns_dnssec_name_node_free,
						    NULL);
			LDNS_FREE(zone->names);
		}
		LDNS_FREE(zone);
	}
}