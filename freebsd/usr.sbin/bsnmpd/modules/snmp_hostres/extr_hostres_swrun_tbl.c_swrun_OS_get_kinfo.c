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
struct swrun_entry {int /*<<< orphan*/  flags; } ;
struct kld_file_stat {int version; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  HR_SWRUN_FOUND ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ NO_PID ; 
 int /*<<< orphan*/  kld_file_stat_to_swrun (struct kld_file_stat*,struct swrun_entry*) ; 
 int kldnext (int) ; 
 scalar_t__ kldstat (int,struct kld_file_stat*) ; 
 struct swrun_entry* swrun_entry_create (scalar_t__) ; 
 struct swrun_entry* swrun_entry_find_by_index (scalar_t__) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
swrun_OS_get_kinfo(void)
{
	int fileid;
	struct swrun_entry *entry;
	struct kld_file_stat stat;

	for (fileid = kldnext(0); fileid > 0; fileid = kldnext(fileid)) {
		stat.version = sizeof(struct kld_file_stat);
		if (kldstat(fileid, &stat) < 0) {
			syslog(LOG_ERR, "kldstat() failed: %m");
			continue;
		}

		/*
		 * kernel and kernel files (*.ko) will be indexed starting with
		 * NO_PID + 1; NO_PID is PID_MAX + 1 thus it will be no risk to
		 * overlap with real PIDs which are in range of 1 .. NO_PID
		 */
		entry = swrun_entry_find_by_index(NO_PID + 1 + stat.id);
		if (entry == NULL) {
			/* new entry - get memory for it */
			entry = swrun_entry_create(NO_PID + 1 + stat.id);
			if (entry == NULL)
				continue;
		}
		entry->flags |= HR_SWRUN_FOUND; /* mark it as found */

		kld_file_stat_to_swrun(&stat, entry);
	}
}