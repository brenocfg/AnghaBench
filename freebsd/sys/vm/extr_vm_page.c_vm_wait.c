#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_object_t ;
struct domainset {int /*<<< orphan*/  ds_mask; } ;
struct TYPE_7__ {struct domainset* dr_policy; } ;
struct TYPE_9__ {TYPE_2__ td_domain; } ;
struct TYPE_6__ {struct domainset* dr_policy; } ;
struct TYPE_8__ {TYPE_1__ domain; } ;

/* Variables and functions */
 TYPE_5__* curthread ; 
 int /*<<< orphan*/  vm_wait_doms (int /*<<< orphan*/ *) ; 

void
vm_wait(vm_object_t obj)
{
	struct domainset *d;

	d = NULL;

	/*
	 * Carefully fetch pointers only once: the struct domainset
	 * itself is ummutable but the pointer might change.
	 */
	if (obj != NULL)
		d = obj->domain.dr_policy;
	if (d == NULL)
		d = curthread->td_domain.dr_policy;

	vm_wait_doms(&d->ds_mask);
}