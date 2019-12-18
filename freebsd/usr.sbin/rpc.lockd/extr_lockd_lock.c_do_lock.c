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
#define  PFL_GRANTED 135 
#define  PFL_GRANTED_DUPLICATE 134 
#define  PFL_HWBLOCKED 133 
#define  PFL_HWDENIED 132 
#define  PFL_HWRESERR 131 
#define  PFL_NFSBLOCKED 130 
#define  PFL_NFSDENIED 129 
#define  PFL_NFSRESERR 128 
 int /*<<< orphan*/  debuglog (char*) ; 
 int /*<<< orphan*/  dump_filelock (struct file_lock*) ; 
 int lock_partialfilelock (struct file_lock*) ; 
 int nlm4_blocked ; 
 int nlm4_denied ; 
 int nlm4_denied_nolocks ; 
 int nlm4_failed ; 
 int nlm4_granted ; 
 int nlm_blocked ; 
 int nlm_denied ; 
 int nlm_denied_nolocks ; 
 int nlm_granted ; 

enum nlm_stats
do_lock(struct file_lock *fl)
{
	enum partialfilelock_status pfsret;
	enum nlm_stats retval;

	debuglog("Entering do_lock...\n");

	pfsret = lock_partialfilelock(fl);

	switch (pfsret) {
	case PFL_GRANTED:
		debuglog("PFL lock granted");
		dump_filelock(fl);
		retval = (fl->flags & LOCK_V4) ? nlm4_granted : nlm_granted;
		break;
	case PFL_GRANTED_DUPLICATE:
		debuglog("PFL lock granted--duplicate id detected");
		dump_filelock(fl);
		retval = (fl->flags & LOCK_V4) ? nlm4_granted : nlm_granted;
		break;
	case PFL_NFSDENIED:
	case PFL_HWDENIED:
		debuglog("PFL_NFS lock denied");
		dump_filelock(fl);
		retval = (fl->flags & LOCK_V4) ? nlm4_denied : nlm_denied;
		break;
	case PFL_NFSBLOCKED:
	case PFL_HWBLOCKED:
		debuglog("PFL_NFS blocking lock denied.  Queued.\n");
		dump_filelock(fl);
		retval = (fl->flags & LOCK_V4) ? nlm4_blocked : nlm_blocked;
		break;
	case PFL_NFSRESERR:
	case PFL_HWRESERR:
		debuglog("PFL lock resource alocation fail\n");
		dump_filelock(fl);
		retval = (fl->flags & LOCK_V4) ? nlm4_denied_nolocks : nlm_denied_nolocks;
		break;
	default:
		debuglog("PFL lock *FAILED*");
		dump_filelock(fl);
		retval = (fl->flags & LOCK_V4) ? nlm4_failed : nlm_denied;
		break;
	}

	debuglog("Exiting do_lock...\n");

	return retval;
}