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
typedef  int /*<<< orphan*/  git_win32_path ;

/* Variables and functions */
 int /*<<< orphan*/  CreateSymbolicLinkW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE ; 
 scalar_t__ git__utf8_to_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ git_win32_path_from_utf8 (int /*<<< orphan*/ ,char const*) ; 

int p_symlink(const char *target, const char *path)
{
	git_win32_path target_w, path_w;

	if (git_win32_path_from_utf8(path_w, path) < 0 ||
		git__utf8_to_16(target_w, MAX_PATH, target) < 0)
		return -1;

	if (!CreateSymbolicLinkW(path_w, target_w,
	    SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE))
		return -1;

	return 0;
}