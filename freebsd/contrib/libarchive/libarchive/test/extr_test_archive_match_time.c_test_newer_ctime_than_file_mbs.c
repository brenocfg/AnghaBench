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
 int ARCHIVE_MATCH_CTIME ; 
 int ARCHIVE_MATCH_NEWER ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_clear (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_match_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_match_free (struct archive*) ; 
 int /*<<< orphan*/  archive_match_include_file_time (struct archive*,int,char*) ; 
 struct archive* archive_match_new () ; 
 int /*<<< orphan*/  archive_match_time_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_disk_entry_from_file (struct archive*,struct archive_entry*,int,int /*<<< orphan*/ *) ; 
 struct archive* archive_read_disk_new () ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*) ; 

__attribute__((used)) static void
test_newer_ctime_than_file_mbs(void)
{
	struct archive *a;
	struct archive_entry *ae;
	struct archive *m;

	if (!assert((m = archive_match_new()) != NULL))
		return;
	if (!assert((ae = archive_entry_new()) != NULL)) {
		archive_match_free(m);
		return;
	}
	if (!assert((a = archive_read_disk_new()) != NULL)) {
		archive_match_free(m);
		archive_entry_free(ae);
		return;
	}

	/*
	 * Test: newer ctime than a file specified in MBS file name.
	 */
	assertEqualIntA(m, 0, archive_match_include_file_time(m,
	    ARCHIVE_MATCH_CTIME | ARCHIVE_MATCH_NEWER, "mid_ctime"));

	/* Verify 'old_ctime' file. */
	archive_entry_copy_pathname(ae, "old_ctime");
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_disk_entry_from_file(a, ae, -1, NULL));
	failure("old_ctime should be excluded");
	assertEqualInt(1, archive_match_time_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));

	/* Verify 'mid_ctime' file. */
	archive_entry_clear(ae);
	archive_entry_copy_pathname(ae, "mid_ctime");
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_disk_entry_from_file(a, ae, -1, NULL));
	failure("mid_ctime should be excluded");
	assertEqualInt(1, archive_match_time_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));

	/* Verify 'new_ctime' file. */
	archive_entry_clear(ae);
	archive_entry_copy_pathname(ae, "new_ctime");
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_disk_entry_from_file(a, ae, -1, NULL));
	failure("new_ctime should not be excluded");
	assertEqualInt(0, archive_match_time_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));

	/* Clean up. */
	archive_read_free(a);
	archive_entry_free(ae);
	archive_match_free(m);
}