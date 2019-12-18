#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct storage_entry {int allocationUnits; int size; int used; int /*<<< orphan*/  index; scalar_t__ allocationFailures; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; } ;
struct statfs {int dummy; } ;
typedef  int /*<<< orphan*/  fs_string ;
struct TYPE_7__ {char* f_mntonname; char* f_fstypename; char* f_mntfromname; int f_bsize; int f_blocks; int f_bfree; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRDBG (char*,int) ; 
 int /*<<< orphan*/  HR_STORAGE_FOUND ; 
 int INT_MAX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int SE_DESC_MLEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* fs_buf ; 
 int fs_buf_count ; 
 int /*<<< orphan*/  fs_get_type (TYPE_1__*) ; 
 int /*<<< orphan*/  fs_tbl_post_refresh () ; 
 int /*<<< orphan*/  fs_tbl_pre_refresh () ; 
 int /*<<< orphan*/  fs_tbl_process_statfs_entry (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int getfsstat (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* reallocf (TYPE_1__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 struct storage_entry* storage_entry_create (char*) ; 
 struct storage_entry* storage_find_by_name (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
storage_OS_get_fs(void)
{
	struct storage_entry *entry;
	uint64_t size, used;
	int i, mounted_fs_count, units;
	char fs_string[SE_DESC_MLEN];

	if ((mounted_fs_count = getfsstat(NULL, 0, MNT_NOWAIT)) < 0) {
		syslog(LOG_ERR, "hrStorageTable: getfsstat() failed: %m");
		return; /* out of luck this time */
	}

	if (mounted_fs_count != (int)fs_buf_count || fs_buf == NULL) {
		fs_buf_count = mounted_fs_count;
		fs_buf = reallocf(fs_buf, fs_buf_count * sizeof(struct statfs));
		if (fs_buf == NULL) {
			fs_buf_count = 0;
			assert(0);
			return;
		}
	}

	if ((mounted_fs_count = getfsstat(fs_buf,
	    fs_buf_count * sizeof(struct statfs), MNT_NOWAIT)) < 0) {
		syslog(LOG_ERR, "hrStorageTable: getfsstat() failed: %m");
		return; /* out of luck this time */
	}

	HRDBG("got %d mounted FS", mounted_fs_count);

	fs_tbl_pre_refresh();

	for (i = 0; i < mounted_fs_count; i++) {
		snprintf(fs_string, sizeof(fs_string),
		    "%s, type: %s, dev: %s", fs_buf[i].f_mntonname,
		    fs_buf[i].f_fstypename, fs_buf[i].f_mntfromname);

		entry = storage_find_by_name(fs_string);
		if (entry == NULL)
			entry = storage_entry_create(fs_string);

		assert (entry != NULL);
		if (entry == NULL)
			return; /* Out of luck */

		entry->flags |= HR_STORAGE_FOUND;
		entry->type = fs_get_type(&fs_buf[i]); /*XXX - This is wrong*/

		units = fs_buf[i].f_bsize;
		size = fs_buf[i].f_blocks;
		used = fs_buf[i].f_blocks - fs_buf[i].f_bfree;
		while (size > INT_MAX) {
			units <<= 1;
			size >>= 1;
			used >>= 1;
		}
		entry->allocationUnits = units;
		entry->size = size;
		entry->used = used;

		entry->allocationFailures = 0;

		/* take care of hrFSTable */
		fs_tbl_process_statfs_entry(&fs_buf[i], entry->index);
	}

	fs_tbl_post_refresh();
}