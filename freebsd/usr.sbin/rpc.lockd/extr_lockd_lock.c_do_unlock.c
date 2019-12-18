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
struct file_lock {int flags; } ;
typedef  enum partialfilelock_status { ____Placeholder_partialfilelock_status } partialfilelock_status ;
typedef  enum nlm_stats { ____Placeholder_nlm_stats } nlm_stats ;

/* Variables and functions */
 int LOCK_V4 ; 
#define  PFL_GRANTED 134 
#define  PFL_HWDENIED 133 
#define  PFL_HWDENIED_NOLOCK 132 
#define  PFL_HWRESERR 131 
#define  PFL_NFSDENIED 130 
#define  PFL_NFSDENIED_NOLOCK 129 
#define  PFL_NFSRESERR 128 
 int /*<<< orphan*/  debuglog (char*) ; 
 int /*<<< orphan*/  dump_filelock (struct file_lock*) ; 
 int nlm4_denied ; 
 int nlm4_denied_nolocks ; 
 int nlm4_failed ; 
 int nlm4_granted ; 
 int nlm_denied ; 
 int nlm_denied_nolocks ; 
 int nlm_granted ; 
 int unlock_partialfilelock (struct file_lock*) ; 

enum nlm_stats
do_unlock(struct file_lock *fl)
{
	enum partialfilelock_status pfsret;
	enum nlm_stats retval;

	debuglog("Entering do_unlock...\n");
	pfsret = unlock_partialfilelock(fl);

	switch (pfsret) {
	case PFL_GRANTED:
		debuglog("PFL unlock granted");
		dump_filelock(fl);
		retval = (fl->flags & LOCK_V4) ? nlm4_granted : nlm_granted;
		break;
	case PFL_NFSDENIED:
	case PFL_HWDENIED:
		debuglog("PFL_NFS unlock denied");
		dump_filelock(fl);
		retval = (fl->flags & LOCK_V4) ? nlm4_denied : nlm_denied;
		break;
	case PFL_NFSDENIED_NOLOCK:
	case PFL_HWDENIED_NOLOCK:
		debuglog("PFL_NFS no lock found\n");
		retval = (fl->flags & LOCK_V4) ? nlm4_granted : nlm_granted;
		break;
	case PFL_NFSRESERR:
	case PFL_HWRESERR:
		debuglog("PFL unlock resource failure");
		dump_filelock(fl);
		retval = (fl->flags & LOCK_V4) ? nlm4_denied_nolocks : nlm_denied_nolocks;
		break;
	default:
		debuglog("PFL unlock *FAILED*");
		dump_filelock(fl);
		retval = (fl->flags & LOCK_V4) ? nlm4_failed : nlm_denied;
		break;
	}

	debuglog("Exiting do_unlock...\n");

	return retval;
}