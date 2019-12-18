#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct local_rrset {TYPE_2__* rrset; struct local_rrset* next; } ;
struct local_data {struct local_rrset* rrsets; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ rk; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_CNAME ; 
 scalar_t__ htons (scalar_t__) ; 

__attribute__((used)) static struct local_rrset*
local_data_find_type(struct local_data* data, uint16_t type, int alias_ok)
{
	struct local_rrset* p;
	type = htons(type);
	for(p = data->rrsets; p; p = p->next) {
		if(p->rrset->rk.type == type)
			return p;
		if(alias_ok && p->rrset->rk.type == htons(LDNS_RR_TYPE_CNAME))
			return p;
	}
	return NULL;
}