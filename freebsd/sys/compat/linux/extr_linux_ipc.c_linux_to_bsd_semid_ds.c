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
struct semid_ds {int /*<<< orphan*/  sem_nsems; int /*<<< orphan*/  sem_ctime; int /*<<< orphan*/  sem_otime; int /*<<< orphan*/  sem_perm; } ;
struct l_semid64_ds {int /*<<< orphan*/  sem_nsems; int /*<<< orphan*/  sem_ctime; int /*<<< orphan*/  sem_otime; int /*<<< orphan*/  sem_perm; } ;

/* Variables and functions */
 int /*<<< orphan*/  linux_to_bsd_ipc_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
linux_to_bsd_semid_ds(struct l_semid64_ds *lsp, struct semid_ds *bsp)
{

	linux_to_bsd_ipc_perm(&lsp->sem_perm, &bsp->sem_perm);
	bsp->sem_otime = lsp->sem_otime;
	bsp->sem_ctime = lsp->sem_ctime;
	bsp->sem_nsems = lsp->sem_nsems;
}