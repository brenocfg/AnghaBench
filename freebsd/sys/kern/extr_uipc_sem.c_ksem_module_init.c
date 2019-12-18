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
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_KSEM ; 
 long SEM_MAX ; 
 long SEM_VALUE_MAX ; 
 int /*<<< orphan*/  SY_THR_STATIC_KLD ; 
 int /*<<< orphan*/  hashinit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksem32_syscalls ; 
 int /*<<< orphan*/  ksem_count_lock ; 
 int /*<<< orphan*/  ksem_dict_lock ; 
 int /*<<< orphan*/  ksem_dictionary ; 
 int /*<<< orphan*/  ksem_hash ; 
 int /*<<< orphan*/  ksem_syscalls ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p31b_setcfg (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  sem_lock ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int syscall32_helper_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int syscall_helper_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ksem_module_init(void)
{
	int error;

	mtx_init(&sem_lock, "sem", NULL, MTX_DEF);
	mtx_init(&ksem_count_lock, "ksem count", NULL, MTX_DEF);
	sx_init(&ksem_dict_lock, "ksem dictionary");
	ksem_dictionary = hashinit(1024, M_KSEM, &ksem_hash);
	p31b_setcfg(CTL_P1003_1B_SEMAPHORES, 200112L);
	p31b_setcfg(CTL_P1003_1B_SEM_NSEMS_MAX, SEM_MAX);
	p31b_setcfg(CTL_P1003_1B_SEM_VALUE_MAX, SEM_VALUE_MAX);

	error = syscall_helper_register(ksem_syscalls, SY_THR_STATIC_KLD);
	if (error)
		return (error);
#ifdef COMPAT_FREEBSD32
	error = syscall32_helper_register(ksem32_syscalls, SY_THR_STATIC_KLD);
	if (error)
		return (error);
#endif
	return (0);
}