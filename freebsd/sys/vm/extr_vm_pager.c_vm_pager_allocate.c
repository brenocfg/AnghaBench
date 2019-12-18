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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
struct ucred {int dummy; } ;
struct pagerops {int /*<<< orphan*/ * (* pgo_alloc ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*) ;} ;
typedef  size_t objtype_t ;

/* Variables and functions */
 struct pagerops** pagertab ; 
 int /*<<< orphan*/ * stub1 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*) ; 

vm_object_t
vm_pager_allocate(objtype_t type, void *handle, vm_ooffset_t size,
    vm_prot_t prot, vm_ooffset_t off, struct ucred *cred)
{
	vm_object_t ret;
	struct pagerops *ops;

	ops = pagertab[type];
	if (ops)
		ret = (*ops->pgo_alloc)(handle, size, prot, off, cred);
	else
		ret = NULL;
	return (ret);
}