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
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 scalar_t__ git__prefixcmp (char*,char*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int check_rref(char *ref)
{
	if (git__prefixcmp(ref, "refs/")) {
		git_error_set(GIT_ERROR_INVALID, "not a valid reference '%s'", ref);
		return -1;
	}

	return 0;
}