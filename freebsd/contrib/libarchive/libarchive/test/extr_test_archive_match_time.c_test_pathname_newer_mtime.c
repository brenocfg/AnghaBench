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
 int ARCHIVE_MATCH_EQUAL ; 
 int ARCHIVE_MATCH_MTIME ; 
 int ARCHIVE_MATCH_OLDER ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_match_exclude_entry (struct archive*,int,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_match_free (struct archive*) ; 
 struct archive* archive_match_new () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  excluded (struct archive*) ; 

__attribute__((used)) static void
test_pathname_newer_mtime(void)
{
	struct archive_entry *ae;
	struct archive *m;

	if (!assert((m = archive_match_new()) != NULL))
		return;
	if (!assert((ae = archive_entry_new()) != NULL)) {
		archive_match_free(m);
		return;
	}

	archive_entry_copy_pathname(ae, "file1");
	archive_entry_set_mtime(ae, 7880, 0);
	assertEqualIntA(m, 0, archive_match_exclude_entry(m,
	    ARCHIVE_MATCH_MTIME | ARCHIVE_MATCH_OLDER |
	    ARCHIVE_MATCH_EQUAL, ae));
	archive_entry_copy_pathname(ae, "file2");
	archive_entry_set_mtime(ae, 1, 0);
	assertEqualIntA(m, 0, archive_match_exclude_entry(m,
	    ARCHIVE_MATCH_MTIME | ARCHIVE_MATCH_OLDER |
	    ARCHIVE_MATCH_EQUAL, ae));
	archive_entry_copy_pathname(ae, "file3");
	archive_entry_set_mtime(ae, 99999, 0);
	assertEqualIntA(m, 0, archive_match_exclude_entry(m,
	    ARCHIVE_MATCH_MTIME | ARCHIVE_MATCH_OLDER |
	    ARCHIVE_MATCH_EQUAL, ae));

	excluded(m);

	/* Clean up. */
	archive_entry_free(ae);
	archive_match_free(m);
}