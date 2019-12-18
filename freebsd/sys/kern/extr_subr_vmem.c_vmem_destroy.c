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
typedef  int /*<<< orphan*/  vmem_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_alllist ; 
 int /*<<< orphan*/  vmem_destroy1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmem_list_lock ; 

void
vmem_destroy(vmem_t *vm)
{

	mtx_lock(&vmem_list_lock);
	LIST_REMOVE(vm, vm_alllist);
	mtx_unlock(&vmem_list_lock);

	vmem_destroy1(vm);
}