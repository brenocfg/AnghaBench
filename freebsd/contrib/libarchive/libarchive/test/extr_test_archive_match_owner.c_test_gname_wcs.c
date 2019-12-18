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
 int /*<<< orphan*/  archive_entry_copy_gname_w (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_match_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_match_free (struct archive*) ; 
 int /*<<< orphan*/  archive_match_include_gname_w (struct archive*,char*) ; 
 struct archive* archive_match_new () ; 
 int /*<<< orphan*/  archive_match_owner_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*) ; 

__attribute__((used)) static void
test_gname_wcs(void)
{
	struct archive_entry *ae;
	struct archive *m;

	if (!assert((m = archive_match_new()) != NULL))
		return;
	if (!assert((ae = archive_entry_new()) != NULL)) {
		archive_match_free(m);
		return;
	}

	assertEqualIntA(m, 0, archive_match_include_gname_w(m, L"foo"));
	assertEqualIntA(m, 0, archive_match_include_gname_w(m, L"bar"));

	archive_entry_copy_gname_w(ae, L"unknown");
	failure("Group 'unknown' should be excluded");
	assertEqualInt(1, archive_match_owner_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));
	archive_entry_copy_gname_w(ae, L"foo");
	failure("Group 'foo' should not be excluded");
	assertEqualInt(0, archive_match_owner_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));
	archive_entry_copy_gname_w(ae, L"foo1");
	failure("Group 'foo1' should be excluded");
	assertEqualInt(1, archive_match_owner_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));
	archive_entry_copy_gname_w(ae, L"bar");
	failure("Group 'bar' should not be excluded");
	assertEqualInt(0, archive_match_owner_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));
	archive_entry_copy_gname_w(ae, L"bar1");
	failure("Group 'bar1' should be excluded");
	assertEqualInt(1, archive_match_owner_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));

	/* Clean up. */
	archive_entry_free(ae);
	archive_match_free(m);
}