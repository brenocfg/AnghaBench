#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ entry; } ;
struct packed_rrset_data {int dummy; } ;
struct iter_qstate {struct iter_prep_list* an_prepend_list; } ;
struct iter_prep_list {struct iter_prep_list* next; TYPE_3__* rrset; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_6__ {TYPE_1__ entry; } ;

/* Variables and functions */
 scalar_t__ rrsetdata_equal (struct packed_rrset_data*,struct packed_rrset_data*) ; 
 scalar_t__ ub_rrset_compare (TYPE_3__*,struct ub_packed_rrset_key*) ; 

__attribute__((used)) static int
iter_find_rrset_in_prepend_answer(struct iter_qstate* iq,
	struct ub_packed_rrset_key* rrset)
{
	struct iter_prep_list* p = iq->an_prepend_list;
	while(p) {
		if(ub_rrset_compare(p->rrset, rrset) == 0 &&
			rrsetdata_equal((struct packed_rrset_data*)p->rrset
			->entry.data, (struct packed_rrset_data*)rrset
			->entry.data))
			return 1;
		p = p->next;
	}
	return 0;
}