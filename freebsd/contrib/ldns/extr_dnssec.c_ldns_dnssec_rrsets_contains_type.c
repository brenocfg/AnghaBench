#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ldns_rr_type ;
struct TYPE_3__ {scalar_t__ type; struct TYPE_3__* next; } ;
typedef  TYPE_1__ ldns_dnssec_rrsets ;

/* Variables and functions */

int
ldns_dnssec_rrsets_contains_type(const ldns_dnssec_rrsets *rrsets,
                                 ldns_rr_type type)
{
	const ldns_dnssec_rrsets *cur_rrset = rrsets;
	while (cur_rrset) {
		if (cur_rrset->type == type) {
			return 1;
		}
		cur_rrset = cur_rrset->next;
	}
	return 0;
}