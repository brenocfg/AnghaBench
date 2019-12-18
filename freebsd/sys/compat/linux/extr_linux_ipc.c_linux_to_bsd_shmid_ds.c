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
struct shmid_ds {int /*<<< orphan*/  shm_ctime; int /*<<< orphan*/  shm_dtime; int /*<<< orphan*/  shm_atime; int /*<<< orphan*/  shm_nattch; int /*<<< orphan*/  shm_cpid; int /*<<< orphan*/  shm_lpid; int /*<<< orphan*/  shm_segsz; int /*<<< orphan*/  shm_perm; } ;
struct l_shmid64_ds {int /*<<< orphan*/  shm_ctime; int /*<<< orphan*/  shm_dtime; int /*<<< orphan*/  shm_atime; int /*<<< orphan*/  shm_nattch; int /*<<< orphan*/  shm_cpid; int /*<<< orphan*/  shm_lpid; int /*<<< orphan*/  shm_segsz; int /*<<< orphan*/  shm_perm; } ;

/* Variables and functions */
 int /*<<< orphan*/  linux_to_bsd_ipc_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
linux_to_bsd_shmid_ds(struct l_shmid64_ds *lsp, struct shmid_ds *bsp)
{

	linux_to_bsd_ipc_perm(&lsp->shm_perm, &bsp->shm_perm);
	bsp->shm_segsz = lsp->shm_segsz;
	bsp->shm_lpid = lsp->shm_lpid;
	bsp->shm_cpid = lsp->shm_cpid;
	bsp->shm_nattch = lsp->shm_nattch;
	bsp->shm_atime = lsp->shm_atime;
	bsp->shm_dtime = lsp->shm_dtime;
	bsp->shm_ctime = lsp->shm_ctime;
}