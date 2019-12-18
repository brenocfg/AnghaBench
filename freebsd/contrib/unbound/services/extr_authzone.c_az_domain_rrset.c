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
typedef  scalar_t__ uint16_t ;
struct auth_rrset {scalar_t__ type; struct auth_rrset* next; } ;
struct auth_data {struct auth_rrset* rrsets; } ;

/* Variables and functions */

__attribute__((used)) static struct auth_rrset*
az_domain_rrset(struct auth_data* n, uint16_t t)
{
	struct auth_rrset* rrset;
	if(!n) return NULL;
	rrset = n->rrsets;
	while(rrset) {
		if(rrset->type == t)
			return rrset;
		rrset = rrset->next;
	}
	return NULL;
}