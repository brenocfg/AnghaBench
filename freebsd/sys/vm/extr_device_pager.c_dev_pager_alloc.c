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
typedef  int /*<<< orphan*/  vm_object_t ;
struct ucred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJT_DEVICE ; 
 int /*<<< orphan*/  cdev_pager_allocate (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*) ; 
 int /*<<< orphan*/  old_dev_pager_ops ; 

__attribute__((used)) static vm_object_t
dev_pager_alloc(void *handle, vm_ooffset_t size, vm_prot_t prot,
    vm_ooffset_t foff, struct ucred *cred)
{

	return (cdev_pager_allocate(handle, OBJT_DEVICE, &old_dev_pager_ops,
	    size, prot, foff, cred));
}