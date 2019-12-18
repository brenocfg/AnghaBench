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
 int /*<<< orphan*/  archive_entry_clear (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname_w (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_match_exclude_pattern (struct archive*,char*) ; 
 int /*<<< orphan*/  archive_match_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_match_free (struct archive*) ; 
 struct archive* archive_match_new () ; 
 int /*<<< orphan*/  archive_match_path_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*) ; 

__attribute__((used)) static void
test_exclusion_mbs(void)
{
	struct archive_entry *ae;
	struct archive *m;

	if (!assert((m = archive_match_new()) != NULL))
		return;
	if (!assert((ae = archive_entry_new()) != NULL)) {
		archive_match_free(m);
		return;
	}

	/* Test for pattern "^aa*" */
	assertEqualIntA(m, 0, archive_match_exclude_pattern(m, "^aa*"));

	/* Test with 'aa1234', which should be excluded. */
	archive_entry_copy_pathname(ae, "aa1234");
	failure("'aa1234' should be excluded");
	assertEqualInt(1, archive_match_path_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));
	archive_entry_clear(ae);
	archive_entry_copy_pathname_w(ae, L"aa1234");
	failure("'aa1234' should be excluded");
	assertEqualInt(1, archive_match_path_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));

	/* Test with 'a1234', which should not be excluded. */
	archive_entry_copy_pathname(ae, "a1234");
	failure("'a1234' should not be excluded");
	assertEqualInt(0, archive_match_path_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));
	archive_entry_clear(ae);
	archive_entry_copy_pathname_w(ae, L"a1234");
	failure("'a1234' should not be excluded");
	assertEqualInt(0, archive_match_path_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));

	/* Clean up. */
	archive_entry_free(ae);
	archive_match_free(m);
}