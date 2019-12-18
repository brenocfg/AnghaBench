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
typedef  struct file_lock const file_lock ;
typedef  enum partialfilelock_status { ____Placeholder_partialfilelock_status } partialfilelock_status ;
typedef  enum nfslock_status { ____Placeholder_nfslock_status } nfslock_status ;

/* Variables and functions */
 int NFS_GRANTED ; 
 int NFS_GRANTED_DUPLICATE ; 
 int PFL_DENIED ; 
 int PFL_GRANTED ; 
 int PFL_GRANTED_DUPLICATE ; 
 int PFL_NFSDENIED ; 
 int /*<<< orphan*/  debuglog (char*,...) ; 
 int /*<<< orphan*/  dump_filelock (struct file_lock const*) ; 
 int test_nfslock (struct file_lock const*,struct file_lock const**) ; 

enum partialfilelock_status
test_partialfilelock(const struct file_lock *fl,
    struct file_lock **conflicting_fl)
{
	enum partialfilelock_status retval;
	enum nfslock_status teststatus;

	debuglog("Entering testpartialfilelock...\n");

	retval = PFL_DENIED;

	teststatus = test_nfslock(fl, conflicting_fl);
	debuglog("test_partialfilelock: teststatus %d\n",teststatus);

	if (teststatus == NFS_GRANTED || teststatus == NFS_GRANTED_DUPLICATE) {
		/* XXX: Add the underlying filesystem locking code */
		retval = (teststatus == NFS_GRANTED) ?
		    PFL_GRANTED : PFL_GRANTED_DUPLICATE;
		debuglog("Dumping locks...\n");
		dump_filelock(fl);
		dump_filelock(*conflicting_fl);
		debuglog("Done dumping locks...\n");
	} else {
		retval = PFL_NFSDENIED;
		debuglog("NFS test denied.\n");
		dump_filelock(fl);
		debuglog("Conflicting.\n");
		dump_filelock(*conflicting_fl);
	}

	debuglog("Exiting testpartialfilelock...\n");

	return retval;
}