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
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_set_gid (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_match_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_match_free (struct archive*) ; 
 int /*<<< orphan*/  archive_match_include_gid (struct archive*,int) ; 
 struct archive* archive_match_new () ; 
 int /*<<< orphan*/  archive_match_owner_excluded (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*) ; 

__attribute__((used)) static void
test_gid(void)
{
	struct archive_entry *ae;
	struct archive *m;

	if (!assert((m = archive_match_new()) != NULL))
		return;
	if (!assert((ae = archive_entry_new()) != NULL)) {
		archive_match_free(m);
		return;
	}

	assertEqualIntA(m, 0, archive_match_include_gid(m, 1000));
	assertEqualIntA(m, 0, archive_match_include_gid(m, 1002));

	archive_entry_set_gid(ae, 0);
	failure("uid 0 should be excluded");
	assertEqualInt(1, archive_match_owner_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));
	archive_entry_set_gid(ae, 1000);
	failure("uid 1000 should not be excluded");
	assertEqualInt(0, archive_match_owner_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));
	archive_entry_set_gid(ae, 1001);
	failure("uid 1001 should be excluded");
	assertEqualInt(1, archive_match_owner_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));
	archive_entry_set_gid(ae, 1002);
	failure("uid 1002 should not be excluded");
	assertEqualInt(0, archive_match_owner_excluded(m, ae));
	assertEqualInt(0, archive_match_excluded(m, ae));
	archive_entry_set_gid(ae, 1003);
	failure("uid 1003 should be excluded");
	assertEqualInt(1, archive_match_owner_excluded(m, ae));
	assertEqualInt(1, archive_match_excluded(m, ae));

	/* Clean up. */
	archive_entry_free(ae);
	archive_match_free(m);
}