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

/* Variables and functions */
 int /*<<< orphan*/  CTL_P1003_1B_SEMAPHORES ; 
 int /*<<< orphan*/  CTL_P1003_1B_SEM_NSEMS_MAX ; 
 int /*<<< orphan*/  CTL_P1003_1B_SEM_VALUE_MAX ; 
 int /*<<< orphan*/  M_KSEM ; 
 int /*<<< orphan*/  hashdestroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksem32_syscalls ; 
 int /*<<< orphan*/  ksem_count_lock ; 
 int /*<<< orphan*/  ksem_dict_lock ; 
 int /*<<< orphan*/  ksem_dictionary ; 
 int /*<<< orphan*/  ksem_hash ; 
 int /*<<< orphan*/  ksem_syscalls ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p31b_setcfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p31b_unsetcfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sem_lock ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscall32_helper_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscall_helper_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ksem_module_destroy(void)
{

#ifdef COMPAT_FREEBSD32
	syscall32_helper_unregister(ksem32_syscalls);
#endif
	syscall_helper_unregister(ksem_syscalls);

	p31b_setcfg(CTL_P1003_1B_SEMAPHORES, 0);
	hashdestroy(ksem_dictionary, M_KSEM, ksem_hash);
	sx_destroy(&ksem_dict_lock);
	mtx_destroy(&ksem_count_lock);
	mtx_destroy(&sem_lock);
	p31b_unsetcfg(CTL_P1003_1B_SEM_VALUE_MAX);
	p31b_unsetcfg(CTL_P1003_1B_SEM_NSEMS_MAX);
}