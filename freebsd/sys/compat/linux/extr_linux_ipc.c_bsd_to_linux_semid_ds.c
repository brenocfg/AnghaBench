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
 int /*<<< orphan*/  bsd_to_linux_ipc_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bsd_to_linux_semid_ds(struct semid_ds *bsp, struct l_semid64_ds *lsp)
{

	bsd_to_linux_ipc_perm(&bsp->sem_perm, &lsp->sem_perm);
	lsp->sem_otime = bsp->sem_otime;
	lsp->sem_ctime = bsp->sem_ctime;
	lsp->sem_nsems = bsp->sem_nsems;
}