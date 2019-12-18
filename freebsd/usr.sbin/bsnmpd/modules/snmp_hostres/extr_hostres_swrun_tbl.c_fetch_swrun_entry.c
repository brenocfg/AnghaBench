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
struct swrun_entry {scalar_t__ index; void* status; } ;
struct kld_file_stat {int version; } ;
struct kinfo_proc {int dummy; } ;
typedef  int /*<<< orphan*/  stat ;
typedef  void* int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRDBG (char*,scalar_t__) ; 
 int /*<<< orphan*/  KERN_PROC_PID ; 
 scalar_t__ NO_PID ; 
 scalar_t__ SRS_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hr_kd ; 
 int /*<<< orphan*/  kinfo_proc_to_swrun_entry (struct kinfo_proc*,struct swrun_entry*) ; 
 int /*<<< orphan*/  kld_file_stat_to_swrun (struct kld_file_stat*,struct swrun_entry*) ; 
 int kldstat (scalar_t__,struct kld_file_stat*) ; 
 struct kinfo_proc* kvm_getprocs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static void
fetch_swrun_entry(struct swrun_entry *entry)
{
	struct kinfo_proc *plist;
	int nproc;
	struct kld_file_stat stat;

	assert(entry !=  NULL);

	if (entry->index >= NO_PID + 1)	{
		/*
		 * kernel and kernel files (*.ko) will be indexed
		 * starting with NO_PID + 1; NO_PID is PID_MAX + 1
		 * thus it will be no risk to overlap with real PIDs
		 * which are in range of 1 .. NO_PID
		 */
		stat.version = sizeof(stat);
		if (kldstat(entry->index - NO_PID - 1, &stat) == -1) {
			/*
			 * not found, it's gone. Mark it as invalid for now, it
			 * will be removed from the list at next global refersh
			 */
			 HRDBG("missing item with kid=%d",
			     entry->index -  NO_PID - 1);
			entry->status = (int32_t)SRS_INVALID;
		} else
			kld_file_stat_to_swrun(&stat, entry);

	} else {
		/* this is a process */
		assert(hr_kd != NULL);
		plist = kvm_getprocs(hr_kd, KERN_PROC_PID,
		    entry->index - 1, &nproc);
		if (plist == NULL || nproc != 1) {
			HRDBG("missing item with PID=%d", entry->index - 1);
			entry->status = (int32_t)SRS_INVALID;
		} else
			kinfo_proc_to_swrun_entry(plist, entry);
	}
}