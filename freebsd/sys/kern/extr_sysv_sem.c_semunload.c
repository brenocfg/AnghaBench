#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int semmni; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SEM ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_sysvsem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osd_jail_deregister (scalar_t__) ; 
 int /*<<< orphan*/  process_exit ; 
 int /*<<< orphan*/ * sem ; 
 int /*<<< orphan*/  sem32_syscalls ; 
 int /*<<< orphan*/  sem_mtx ; 
 scalar_t__ sem_prison_slot ; 
 int /*<<< orphan*/  sem_syscalls ; 
 int /*<<< orphan*/  sem_undo_mtx ; 
 int /*<<< orphan*/ * sema ; 
 int /*<<< orphan*/ * sema_mtx ; 
 int /*<<< orphan*/  semexit_tag ; 
 TYPE_1__ seminfo ; 
 scalar_t__ semtot ; 
 int /*<<< orphan*/ * semu ; 
 int /*<<< orphan*/  syscall32_helper_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscall_helper_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
semunload(void)
{
	int i;

	/* XXXKIB */
	if (semtot != 0)
		return (EBUSY);

#ifdef COMPAT_FREEBSD32
	syscall32_helper_unregister(sem32_syscalls);
#endif
	syscall_helper_unregister(sem_syscalls);
	EVENTHANDLER_DEREGISTER(process_exit, semexit_tag);
	if (sem_prison_slot != 0)
		osd_jail_deregister(sem_prison_slot);
#ifdef MAC
	for (i = 0; i < seminfo.semmni; i++)
		mac_sysvsem_destroy(&sema[i]);
#endif
	free(sem, M_SEM);
	free(sema, M_SEM);
	free(semu, M_SEM);
	for (i = 0; i < seminfo.semmni; i++)
		mtx_destroy(&sema_mtx[i]);
	free(sema_mtx, M_SEM);
	mtx_destroy(&sem_mtx);
	mtx_destroy(&sem_undo_mtx);
	return (0);
}