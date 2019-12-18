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
typedef  struct file_lock {int /*<<< orphan*/  client_name; } const file_lock ;
typedef  enum partialfilelock_status { ____Placeholder_partialfilelock_status } partialfilelock_status ;
typedef  enum nfslock_status { ____Placeholder_nfslock_status } nfslock_status ;
typedef  enum hwlock_status { ____Placeholder_hwlock_status } hwlock_status ;

/* Variables and functions */
#define  HW_DENIED_NOLOCK 131 
#define  HW_GRANTED 130 
 int HW_GRANTED_DUPLICATE ; 
#define  NFS_DENIED_NOLOCK 129 
#define  NFS_GRANTED 128 
 int NFS_RESERR ; 
 int PFL_DENIED ; 
 int PFL_GRANTED ; 
 int PFL_HWRESERR ; 
 int PFL_NFSRESERR ; 
 int /*<<< orphan*/  deallocate_file_lock (struct file_lock const*) ; 
 int /*<<< orphan*/  debuglog (char*,...) ; 
 int /*<<< orphan*/  dump_filelock (struct file_lock const*) ; 
 int lock_hwlock (struct file_lock const*) ; 
 int /*<<< orphan*/  monitor_lock_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retry_blockingfilelocklist () ; 
 int unlock_hwlock (struct file_lock const*) ; 
 int unlock_nfslock (struct file_lock const*,struct file_lock const**,struct file_lock const**,struct file_lock const**) ; 
 int /*<<< orphan*/  unmonitor_lock_host (int /*<<< orphan*/ ) ; 

enum partialfilelock_status
unlock_partialfilelock(const struct file_lock *fl)
{
	struct file_lock *lfl,*rfl,*releasedfl,*selffl;
	enum partialfilelock_status retval;
	enum nfslock_status unlstatus;
	enum hwlock_status unlhwstatus, lhwstatus;

	debuglog("Entering unlock_partialfilelock\n");

	selffl = NULL;
	lfl = NULL;
	rfl = NULL;
	releasedfl = NULL;
	retval = PFL_DENIED;

	/*
	 * There are significant overlap and atomicity issues
	 * with partially releasing a lock.  For example, releasing
	 * part of an NFS shared lock does *not* always release the
	 * corresponding part of the file since there is only one
	 * rpc.lockd UID but multiple users could be requesting it
	 * from NFS.  Also, an unlock request should never allow
	 * another process to gain a lock on the remaining parts.
	 * ie. Always apply the new locks before releasing the
	 * old one
	 */

	/*
	 * Loop is required since multiple little locks
	 * can be allocated and then deallocated with one
	 * big unlock.
	 *
	 * The loop is required to be here so that the nfs &
	 * hw subsystems do not need to communicate with one
	 * one another
	 */

	do {
		debuglog("Value of releasedfl: %p\n",releasedfl);
		/* lfl&rfl are created *AND* placed into the NFS lock list if required */
		unlstatus = unlock_nfslock(fl, &releasedfl, &lfl, &rfl);
		debuglog("Value of releasedfl: %p\n",releasedfl);


		/* XXX: This is grungy.  It should be refactored to be cleaner */
		if (lfl != NULL) {
			lhwstatus = lock_hwlock(lfl);
			if (lhwstatus != HW_GRANTED &&
			    lhwstatus != HW_GRANTED_DUPLICATE) {
				debuglog("HW duplicate lock failure for left split\n");
			}
			monitor_lock_host(lfl->client_name);
		}

		if (rfl != NULL) {
			lhwstatus = lock_hwlock(rfl);
			if (lhwstatus != HW_GRANTED &&
			    lhwstatus != HW_GRANTED_DUPLICATE) {
				debuglog("HW duplicate lock failure for right split\n");
			}
			monitor_lock_host(rfl->client_name);
		}

		switch (unlstatus) {
		case NFS_GRANTED:
			/* Attempt to unlock on the hardware */
			debuglog("NFS unlock granted.  Attempting hardware unlock\n");

			/* This call *MUST NOT* unlock the two newly allocated locks */
			unlhwstatus = unlock_hwlock(fl);
			debuglog("HW unlock returned with code %d\n",unlhwstatus);

			switch (unlhwstatus) {
			case HW_GRANTED:
				debuglog("HW unlock granted\n");
				unmonitor_lock_host(releasedfl->client_name);
				retval = PFL_GRANTED;
				break;
			case HW_DENIED_NOLOCK:
				/* Huh?!?!  This shouldn't happen */
				debuglog("HW unlock denied no lock\n");
				retval = PFL_HWRESERR;
				/* Break out of do-while */
				unlstatus = NFS_RESERR;
				break;
			default:
				debuglog("HW unlock failed\n");
				retval = PFL_HWRESERR;
				/* Break out of do-while */
				unlstatus = NFS_RESERR;
				break;
			}

			debuglog("Exiting with status retval: %d\n",retval);

			retry_blockingfilelocklist();
			break;
		case NFS_DENIED_NOLOCK:
			retval = PFL_GRANTED;
			debuglog("All locks cleaned out\n");
			break;
		default:
			retval = PFL_NFSRESERR;
			debuglog("NFS unlock failure\n");
			dump_filelock(fl);
			break;
		}

		if (releasedfl != NULL) {
			if (fl == releasedfl) {
				/*
				 * XXX: YECHHH!!! Attempt to unlock self succeeded
				 * but we can't deallocate the space yet.  This is what
				 * happens when you don't write malloc and free together
				 */
				debuglog("Attempt to unlock self\n");
				selffl = releasedfl;
			} else {
				/*
				 * XXX: this deallocation *still* needs to migrate closer
				 * to the allocation code way up in get_lock or the allocation
				 * code needs to migrate down (violation of "When you write
				 * malloc you must write free")
				 */

				deallocate_file_lock(releasedfl);
				releasedfl = NULL;
			}
		}

	} while (unlstatus == NFS_GRANTED);

	if (selffl != NULL) {
		/*
		 * This statement wipes out the incoming file lock (fl)
		 * in spite of the fact that it is declared const
		 */
		debuglog("WARNING!  Destroying incoming lock pointer\n");
		deallocate_file_lock(selffl);
	}

	debuglog("Exiting unlock_partialfilelock\n");

	return retval;
}