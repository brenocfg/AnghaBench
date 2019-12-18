#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive_read_disk {int /*<<< orphan*/  flags; int /*<<< orphan*/  archive; TYPE_1__* tree; } ;
struct archive {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READDISK_RESTORE_ATIME ; 
 int /*<<< orphan*/  ARCHIVE_READ_DISK_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_ANY ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  needsRestoreTimes ; 

int
archive_read_disk_set_atime_restored(struct archive *_a)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_ANY, "archive_read_disk_restore_atime");
#ifdef HAVE_UTIMES
	a->flags |= ARCHIVE_READDISK_RESTORE_ATIME;
	if (a->tree != NULL)
		a->tree->flags |= needsRestoreTimes;
	return (ARCHIVE_OK);
#else
	/* Display warning and unset flag */
	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
	    "Cannot restore access time on this system");
	a->flags &= ~ARCHIVE_READDISK_RESTORE_ATIME;
	return (ARCHIVE_WARN);
#endif
}