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
struct ub_packed_rrset_key {int dummy; } ;
struct module_qstate {int /*<<< orphan*/  region; } ;
struct iter_qstate {struct iter_prep_list* an_prepend_last; struct iter_prep_list* an_prepend_list; } ;
struct iter_prep_list {struct iter_prep_list* next; struct ub_packed_rrset_key* rrset; } ;

/* Variables and functions */
 scalar_t__ regional_alloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iter_add_prepend_answer(struct module_qstate* qstate, struct iter_qstate* iq,
	struct ub_packed_rrset_key* rrset)
{
	struct iter_prep_list* p = (struct iter_prep_list*)regional_alloc(
		qstate->region, sizeof(struct iter_prep_list));
	if(!p)
		return 0;
	p->rrset = rrset;
	p->next = NULL;
	/* add at end */
	if(iq->an_prepend_last)
		iq->an_prepend_last->next = p;
	else	iq->an_prepend_list = p;
	iq->an_prepend_last = p;
	return 1;
}