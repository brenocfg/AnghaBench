#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct reply_info {size_t rrset_count; struct ub_packed_rrset_key** rrsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_NS ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ub_packed_rrset_key*
reply_get_NS_rrset(struct reply_info* rep)
{
	size_t i;
	for(i=0; i<rep->rrset_count; i++) {
		if(rep->rrsets[i]->rk.type == htons(LDNS_RR_TYPE_NS)) {
			return rep->rrsets[i];
		}
	}
	return NULL;
}