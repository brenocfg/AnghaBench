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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/ * dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;

/* Variables and functions */
 scalar_t__ dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dname_get_shared_topdomain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsec_get_next (struct ub_packed_rrset_key*,int /*<<< orphan*/ **,size_t*) ; 

uint8_t* 
nsec_closest_encloser(uint8_t* qname, struct ub_packed_rrset_key* nsec)
{
	uint8_t* next;
	size_t nlen;
	uint8_t* common1, *common2;
	if(!nsec_get_next(nsec, &next, &nlen))
		return NULL;
	/* longest common with owner or next name */
	common1 = dname_get_shared_topdomain(nsec->rk.dname, qname);
	common2 = dname_get_shared_topdomain(next, qname);
	if(dname_count_labels(common1) > dname_count_labels(common2))
		return common1;
	return common2;
}