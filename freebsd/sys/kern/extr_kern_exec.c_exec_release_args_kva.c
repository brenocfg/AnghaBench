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
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ u_int ;
struct exec_args_kva {scalar_t__ gen; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MADV_FREE ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct exec_args_kva*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_cmpset_ptr (uintptr_t*,uintptr_t,uintptr_t) ; 
 int /*<<< orphan*/  exec_args_kva ; 
 int /*<<< orphan*/  exec_args_kva_freelist ; 
 int /*<<< orphan*/  exec_args_kva_mtx ; 
 int /*<<< orphan*/  exec_map ; 
 scalar_t__ exec_map_entry_size ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  vm_map_madvise (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
exec_release_args_kva(struct exec_args_kva *argkva, u_int gen)
{
	vm_offset_t base;

	base = argkva->addr;
	if (argkva->gen != gen) {
		(void)vm_map_madvise(exec_map, base, base + exec_map_entry_size,
		    MADV_FREE);
		argkva->gen = gen;
	}
	if (!atomic_cmpset_ptr((uintptr_t *)DPCPU_PTR(exec_args_kva),
	    (uintptr_t)NULL, (uintptr_t)argkva)) {
		mtx_lock(&exec_args_kva_mtx);
		SLIST_INSERT_HEAD(&exec_args_kva_freelist, argkva, next);
		wakeup_one(&exec_args_kva_freelist);
		mtx_unlock(&exec_args_kva_mtx);
	}
}