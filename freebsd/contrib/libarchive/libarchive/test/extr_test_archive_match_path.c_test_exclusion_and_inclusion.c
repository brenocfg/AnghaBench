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
typedef  int /*<<< orphan*/  wchar_t ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_clear (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname_w (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_match_exclude_pattern (struct archive*,char*) ; 
 int /*<<< orphan*/  archive_match_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_match_free (struct archive*) ; 
 int /*<<< orphan*/  archive_match_include_pattern (struct archive*,char*) ; 
 int /*<<< orphan*/  archive_match_include_pattern_w (struct archive*,char*) ; 
 struct archive* archive_match_new () ; 
 int /*<<< orphan*/  archive_match_path_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_match_path_unmatched_inclusions (struct archive*) ; 
 int /*<<< orphan*/  archive_match_path_unmatched_inclusions_next (struct archive*,char const**) ; 
 int /*<<< orphan*/  archive_match_path_unmatched_inclusions_next_w (struct archive*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,char const*) ; 
 int /*<<< orphan*/  assertEqualWString (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  failure (char*) ; 

__attribute__((used)) static void
test_exclusion_and_inclusion(void)
{
	struct archive_entry *ae;
	struct archive *m;
	const char *mp;
	const wchar_t *wp;

	if (!assert((m = archive_match_new()) != NULL))
		return;
	if (!assert((ae = archive_entry_new()) != NULL)) {
		archive_match_free(m);
		return;
	}

	assertEqualIntA(m, 0, archive_match_exclude_pattern(m, "^aaa*"));
	assertEqualIntA(m, 0, archive_match_include_pattern_w(m, L"^aa*"));
	assertEqualIntA(m, 0, archive_match_include_pattern(m, "^a1*"));

	/* Test with 'aa1234', which should not be excluded. */
	archive_entry_copy_pathname(ae, "aa1234");
	failure("'aa1234' should not be excluded");
	assertEqualInt(0, archive_match_path_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));
	archive_entry_clear(ae);
	archive_entry_copy_pathname_w(ae, L"aa1234");
	failure("'aa1234' should not be excluded");
	assertEqualInt(0, archive_match_path_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));

	/* Test with 'aaa1234', which should be excluded. */
	archive_entry_copy_pathname(ae, "aaa1234");
	failure("'aaa1234' should be excluded");
	assertEqualInt(1, archive_match_path_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));
	archive_entry_clear(ae);
	archive_entry_copy_pathname_w(ae, L"aaa1234");
	failure("'aaa1234' should be excluded");
	assertEqualInt(1, archive_match_path_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));

	/* Verify unmatched_inclusions. */
	assertEqualInt(1, archive_match_path_unmatched_inclusions(m));
	/* Verify unmatched inclusion patterns. */
	assertEqualIntA(m, ARCHIVE_OK,
	    archive_match_path_unmatched_inclusions_next(m, &mp));
	assertEqualString("^a1*", mp);
	assertEqualIntA(m, ARCHIVE_EOF,
	    archive_match_path_unmatched_inclusions_next(m, &mp));
	/* Verify unmatched inclusion patterns again in Wide-Char. */
	assertEqualIntA(m, ARCHIVE_OK,
	    archive_match_path_unmatched_inclusions_next_w(m, &wp));
	assertEqualWString(L"^a1*", wp);
	assertEqualIntA(m, ARCHIVE_EOF,
	    archive_match_path_unmatched_inclusions_next_w(m, &wp));

	/* Clean up. */
	archive_entry_free(ae);
	archive_match_free(m);
}