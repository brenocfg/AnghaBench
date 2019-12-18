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
struct kinfo_proc {int ki_stat; } ;
typedef  enum SWRunStatus { ____Placeholder_SWRunStatus } SWRunStatus ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
#define  SIDL 134 
#define  SLOCK 133 
 int SRS_INVALID ; 
 int SRS_NOT_RUNNABLE ; 
 int SRS_RUNNABLE ; 
 int SRS_RUNNING ; 
#define  SRUN 132 
#define  SSLEEP 131 
#define  SSTOP 130 
#define  SWAIT 129 
#define  SZOMB 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static enum SWRunStatus
swrun_OS_get_proc_status(const struct kinfo_proc *kp)
{

	assert(kp != NULL);
	if(kp ==  NULL) {
		return (SRS_INVALID);
	}

	/*
	 * I'm using the old style flags - they look cleaner to me,
	 * at least for the purpose of this SNMP table
	 */
	switch (kp->ki_stat) {

	case SSTOP:
		return (SRS_NOT_RUNNABLE);

	case SWAIT:
	case SLOCK:
	case SSLEEP:
		return (SRS_RUNNABLE);

	case SZOMB:
		return (SRS_INVALID);

	case SIDL:
	case SRUN:
		return (SRS_RUNNING);

	default:
		syslog(LOG_ERR,"Unknown process state: %d", kp->ki_stat);
		return (SRS_INVALID);
	}
}