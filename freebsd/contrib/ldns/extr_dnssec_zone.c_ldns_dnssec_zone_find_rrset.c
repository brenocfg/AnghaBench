#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rdf ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_1__ ldns_rbnode_t ;
struct TYPE_6__ {int /*<<< orphan*/  names; } ;
typedef  TYPE_2__ ldns_dnssec_zone ;
typedef  int /*<<< orphan*/  ldns_dnssec_rrsets ;
typedef  int /*<<< orphan*/  ldns_dnssec_name ;

/* Variables and functions */
 int /*<<< orphan*/ * ldns_dnssec_name_find_rrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ldns_rbtree_search (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

ldns_dnssec_rrsets *
ldns_dnssec_zone_find_rrset(const ldns_dnssec_zone *zone,
					   const ldns_rdf *dname,
					   ldns_rr_type type)
{
	ldns_rbnode_t *node;

	if (!zone || !dname || !zone->names) {
		return NULL;
	}

	node = ldns_rbtree_search(zone->names, dname);
	if (node) {
		return ldns_dnssec_name_find_rrset((ldns_dnssec_name *)node->data,
									type);
	} else {
		return NULL;
	}
}