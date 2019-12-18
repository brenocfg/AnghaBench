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
struct smbiod {int iod_flags; int /*<<< orphan*/  iod_evlock; int /*<<< orphan*/  iod_rqlock; int /*<<< orphan*/  iod_sleeptimo; int /*<<< orphan*/  iod_td; int /*<<< orphan*/  iod_scred; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  M_SMBIOD ; 
 int /*<<< orphan*/  PWAIT ; 
 int /*<<< orphan*/  SMBIODEBUG (char*,int /*<<< orphan*/ ) ; 
 int SMBIOD_SHUTDOWN ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  free (struct smbiod*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_iod_main (struct smbiod*) ; 
 int /*<<< orphan*/  smb_makescred (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_sl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsleep (int*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
smb_iod_thread(void *arg)
{
	struct smbiod *iod = arg;

	mtx_lock(&Giant);

	/*
	 * Here we assume that the thread structure will be the same
	 * for an entire kthread (kproc, to be more precise) life.
	 */
	iod->iod_td = curthread;
	smb_makescred(&iod->iod_scred, iod->iod_td, NULL);
	while ((iod->iod_flags & SMBIOD_SHUTDOWN) == 0) {
		smb_iod_main(iod);
		SMBIODEBUG("going to sleep for %d ticks\n", iod->iod_sleeptimo);
		if (iod->iod_flags & SMBIOD_SHUTDOWN)
			break;
		tsleep(&iod->iod_flags, PWAIT, "90idle", iod->iod_sleeptimo);
	}

	/* We can now safely destroy the mutexes and free the iod structure. */
	smb_sl_destroy(&iod->iod_rqlock);
	smb_sl_destroy(&iod->iod_evlock);
	free(iod, M_SMBIOD);
	mtx_unlock(&Giant);
	kproc_exit(0);
}