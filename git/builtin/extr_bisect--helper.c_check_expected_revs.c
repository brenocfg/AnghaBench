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

/* Variables and functions */
 int /*<<< orphan*/  git_path_bisect_ancestors_ok () ; 
 int /*<<< orphan*/  git_path_bisect_expected_rev () ; 
 int /*<<< orphan*/  is_expected_rev (char const*) ; 
 int /*<<< orphan*/  unlink_or_warn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_expected_revs(const char **revs, int rev_nr)
{
	int i;

	for (i = 0; i < rev_nr; i++) {
		if (!is_expected_rev(revs[i])) {
			unlink_or_warn(git_path_bisect_ancestors_ok());
			unlink_or_warn(git_path_bisect_expected_rev());
		}
	}
}