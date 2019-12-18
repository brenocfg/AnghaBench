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
typedef  scalar_t__ ldns_rr_type ;
struct TYPE_5__ {scalar_t__ type; struct TYPE_5__* next; } ;
typedef  TYPE_1__ ldns_dnssec_rrsets ;
struct TYPE_6__ {TYPE_1__* rrsets; } ;
typedef  TYPE_2__ ldns_dnssec_name ;

/* Variables and functions */

ldns_dnssec_rrsets *
ldns_dnssec_name_find_rrset(const ldns_dnssec_name *name,
					   ldns_rr_type type) {
	ldns_dnssec_rrsets *result;

	result = name->rrsets;
	while (result) {
		if (result->type == type) {
			return result;
		} else {
			result = result->next;
		}
	}
	return NULL;
}