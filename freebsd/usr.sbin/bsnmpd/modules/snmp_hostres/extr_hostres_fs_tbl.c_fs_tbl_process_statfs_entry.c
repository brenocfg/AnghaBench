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
struct statfs {int f_flags; char* f_mntfromname; int /*<<< orphan*/  f_mntonname; } ;
struct fs_entry {int /*<<< orphan*/  index; int /*<<< orphan*/  lastPartialBackupDate; int /*<<< orphan*/  lastFullBackupDate; int /*<<< orphan*/  storageIndex; int /*<<< orphan*/  bootable; int /*<<< orphan*/  access; int /*<<< orphan*/  type; void* remoteMountPoint; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FS_READ_ONLY ; 
 int /*<<< orphan*/  FS_READ_WRITE ; 
 int /*<<< orphan*/  HRDBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HR_FS_FOUND ; 
 int MNT_LOCAL ; 
 int MNT_RDONLY ; 
 int MNT_ROOTFS ; 
 int /*<<< orphan*/  TRUTH_MK (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct fs_entry* fs_entry_create (int /*<<< orphan*/ ) ; 
 struct fs_entry* fs_find_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_get_type (struct statfs const*) ; 
 int /*<<< orphan*/  handle_partition_fs_index (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* strdup (char*) ; 

void
fs_tbl_process_statfs_entry(const struct statfs *fs_p, int32_t storage_idx)
{
	struct fs_entry *entry;

	assert(fs_p != 0);

	HRDBG("for hrStorageEntry::index %d", storage_idx);

	if (fs_p == NULL)
		return;

	if ((entry = fs_find_by_name(fs_p->f_mntonname)) != NULL ||
	    (entry = fs_entry_create(fs_p->f_mntonname)) != NULL) {
		entry->flags |= HR_FS_FOUND;

		if (!(fs_p->f_flags & MNT_LOCAL)) {
			/* this is a remote mount */
			entry->remoteMountPoint = strdup(fs_p->f_mntfromname);
			/* if strdup failed, let it be NULL */

		} else {
			entry->remoteMountPoint = strdup("");
			/* if strdup failed, let it be NULL */
		}

		entry->type = fs_get_type(fs_p);

		if ((fs_p->f_flags & MNT_RDONLY) == MNT_RDONLY)
			entry->access = FS_READ_ONLY;
		else
			entry->access = FS_READ_WRITE;

		/* FIXME - bootable fs ?! */
		entry->bootable = TRUTH_MK((fs_p->f_flags & MNT_ROOTFS)
		    == MNT_ROOTFS);

		entry->storageIndex = storage_idx;

		/* Info not available */
		memset(entry->lastFullBackupDate, 0,
		    sizeof(entry->lastFullBackupDate));

		/* Info not available */
		memset(entry->lastPartialBackupDate, 0,
		    sizeof(entry->lastPartialBackupDate));

		handle_partition_fs_index(fs_p->f_mntfromname, entry->index);
	}
}