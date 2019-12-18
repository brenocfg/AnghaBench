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
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_match_exclude_pattern_from_file (struct archive*,char*,int) ; 
 int /*<<< orphan*/  archive_match_free (struct archive*) ; 
 struct archive* archive_match_new () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exclusion_from_file (struct archive*) ; 

__attribute__((used)) static void
test_exclusion_from_file_mbs(void)
{
	struct archive *m;

	/* Test1: read exclusion patterns from file */
	if (!assert((m = archive_match_new()) != NULL))
		return;
	assertEqualIntA(m, 0,
	    archive_match_exclude_pattern_from_file(m, "exclusion", 0));
	exclusion_from_file(m);
	/* Clean up. */
	archive_match_free(m);

	/* Test2: read exclusion patterns in a null separator from file */
	if (!assert((m = archive_match_new()) != NULL))
		return;
	/* Test for pattern reading from file */
	assertEqualIntA(m, 0,
	    archive_match_exclude_pattern_from_file(m, "exclusion_null", 1));
	exclusion_from_file(m);
	/* Clean up. */
	archive_match_free(m);
}