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
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int,int) ; 
 int /*<<< orphan*/  archive_match_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_match_time_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*) ; 

__attribute__((used)) static void
excluded(struct archive *m)
{
	struct archive_entry *ae;

	if (!assert((ae = archive_entry_new()) != NULL))
		return;

	archive_entry_copy_pathname(ae, "file1");
	archive_entry_set_mtime(ae, 7879, 999);
	failure("It should be excluded");
	assertEqualInt(1, archive_match_time_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));
	archive_entry_set_mtime(ae, 7880, 0);
	failure("It should be excluded");
	assertEqualInt(1, archive_match_time_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));
	archive_entry_set_mtime(ae, 7880, 1);
	failure("It should not be excluded");
	assertEqualInt(0, archive_match_time_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));

	archive_entry_copy_pathname(ae, "file2");
	archive_entry_set_mtime(ae, 7879, 999);
	failure("It should not be excluded");
	assertEqualInt(0, archive_match_time_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));
	archive_entry_set_mtime(ae, 7880, 0);
	failure("It should not be excluded");
	assertEqualInt(0, archive_match_time_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));
	archive_entry_set_mtime(ae, 7880, 1);
	failure("It should not be excluded");
	assertEqualInt(0, archive_match_time_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));

	archive_entry_copy_pathname(ae, "file3");
	archive_entry_set_mtime(ae, 7879, 999);
	failure("It should be excluded");
	assertEqualInt(1, archive_match_time_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));
	archive_entry_set_mtime(ae, 7880, 0);
	failure("It should be excluded");
	assertEqualInt(1, archive_match_time_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));
	archive_entry_set_mtime(ae, 7880, 1);
	failure("It should be excluded");
	assertEqualInt(1, archive_match_time_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));

	/*
	 * "file4" is not registered, that sort of a file should not be
	 * excluded with any mtime.
	 */
	archive_entry_copy_pathname(ae, "file4");
	archive_entry_set_mtime(ae, 7879, 999);
	failure("It should not be excluded");
	assertEqualInt(0, archive_match_time_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));
	archive_entry_set_mtime(ae, 7880, 0);
	failure("It should not be excluded");
	assertEqualInt(0, archive_match_time_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));
	archive_entry_set_mtime(ae, 7880, 1);
	failure("It should not be excluded");
	assertEqualInt(0, archive_match_time_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));


	/* Clean up. */
	archive_entry_free(ae);
}