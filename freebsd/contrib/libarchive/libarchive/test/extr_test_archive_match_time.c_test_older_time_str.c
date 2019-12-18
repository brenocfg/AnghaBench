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
typedef  int /*<<< orphan*/  time_t ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_MATCH_CTIME ; 
 int ARCHIVE_MATCH_EQUAL ; 
 int ARCHIVE_MATCH_MTIME ; 
 int ARCHIVE_MATCH_OLDER ; 
 int /*<<< orphan*/  __archive_get_date (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_set_ctime (struct archive_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_match_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_match_free (struct archive*) ; 
 int /*<<< orphan*/  archive_match_include_date (struct archive*,int,char*) ; 
 struct archive* archive_match_new () ; 
 int /*<<< orphan*/  archive_match_time_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_older_time_str(void)
{
	struct archive_entry *ae;
	struct archive *m;
	time_t now, t;

	if (!assert((m = archive_match_new()) != NULL))
		return;
	if (!assert((ae = archive_entry_new()) != NULL)) {
		archive_match_free(m);
		return;
	}

	time(&now);

	/* Test1: Allow newer time. */
	assertEqualIntA(m, 0, archive_match_include_date(m,
	    ARCHIVE_MATCH_MTIME | ARCHIVE_MATCH_CTIME |
	    ARCHIVE_MATCH_OLDER, "1980/2/1 0:0:0 UTC"));

	archive_entry_copy_pathname(ae, "file1");
	t = __archive_get_date(now, "1980/2/1 0:0:0 UTC");
	archive_entry_set_mtime(ae, t, 0);
	archive_entry_set_ctime(ae, t, 0);
	failure("Both Its mtime and ctime should be excluded");
	assertEqualInt(1, archive_match_time_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));
	t = __archive_get_date(now, "1980/1/1 0:0:0 UTC");
	archive_entry_set_mtime(ae, t, 0);
	archive_entry_set_ctime(ae, t, 0);
	failure("Both Its mtime and ctime should not be excluded");
	assertEqualInt(0, archive_match_time_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));

	t = __archive_get_date(now, "1980/3/1 0:0:0 UTC");
	archive_entry_set_mtime(ae, t, 0);
	archive_entry_set_ctime(ae, t, 0);
	failure("Both Its mtime and ctime should be excluded");
	assertEqualInt(1, archive_match_time_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));

	t = __archive_get_date(now, "1980/3/1 0:0:0 UTC");
	archive_entry_set_mtime(ae, t, 0);
	t = __archive_get_date(now, "1980/1/1 0:0:0 UTC");
	archive_entry_set_ctime(ae, t, 0);
	failure("Its mtime should be excluded");
	assertEqualInt(1, archive_match_time_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));

	t = __archive_get_date(now, "1980/1/1 0:0:0 UTC");
	archive_entry_set_mtime(ae, t, 0);
	t = __archive_get_date(now, "1980/3/1 0:0:0 UTC");
	archive_entry_set_ctime(ae, t, 0);
	failure("Its ctime should be excluded");
	assertEqualInt(1, archive_match_time_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));

	/* Test2: Allow equal or newer time. */
	assertEqualIntA(m, 0, archive_match_include_date(m,
	    ARCHIVE_MATCH_MTIME | ARCHIVE_MATCH_CTIME |
	    ARCHIVE_MATCH_OLDER | ARCHIVE_MATCH_EQUAL,
	    "1980/2/1 0:0:0 UTC"));

	archive_entry_copy_pathname(ae, "file1");
	t = __archive_get_date(now, "1980/2/1 0:0:0 UTC");
	archive_entry_set_mtime(ae, t, 0);
	archive_entry_set_ctime(ae, t, 0);
	failure("Both Its mtime and ctime should not be excluded");
	assertEqualInt(0, archive_match_time_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));
	t = __archive_get_date(now, "1980/1/1 0:0:0 UTC");
	archive_entry_set_mtime(ae, t, 0);
	archive_entry_set_ctime(ae, t, 0);
	failure("Both Its mtime and ctime should not be excluded");
	assertEqualInt(0, archive_match_time_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));

	t = __archive_get_date(now, "1980/3/1 0:0:0 UTC");
	archive_entry_set_mtime(ae, t, 0);
	archive_entry_set_ctime(ae, t, 0);
	failure("Both Its mtime and ctime should be excluded");
	assertEqualInt(1, archive_match_time_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));

	/* Clean up. */
	archive_entry_free(ae);
	archive_match_free(m);
}