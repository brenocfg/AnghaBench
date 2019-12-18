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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct exec_args_kva {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ DPCPU_PTR (int /*<<< orphan*/ ) ; 
 struct exec_args_kva* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_readandclear_ptr (uintptr_t*) ; 
 int /*<<< orphan*/  exec_args_kva ; 
 int /*<<< orphan*/  exec_args_kva_freelist ; 
 int /*<<< orphan*/  exec_args_kva_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static vm_offset_t
exec_alloc_args_kva(void **cookie)
{
	struct exec_args_kva *argkva;

	argkva = (void *)atomic_readandclear_ptr(
	    (uintptr_t *)DPCPU_PTR(exec_args_kva));
	if (argkva == NULL) {
		mtx_lock(&exec_args_kva_mtx);
		while ((argkva = SLIST_FIRST(&exec_args_kva_freelist)) == NULL)
			(void)mtx_sleep(&exec_args_kva_freelist,
			    &exec_args_kva_mtx, 0, "execkva", 0);
		SLIST_REMOVE_HEAD(&exec_args_kva_freelist, next);
		mtx_unlock(&exec_args_kva_mtx);
	}
	*(struct exec_args_kva **)cookie = argkva;
	return (argkva->addr);
}