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
 int /*<<< orphan*/  do_with_retries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_writable (int /*<<< orphan*/ ) ; 
 scalar_t__ git_win32_path_from_utf8 (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  unlink_once (int /*<<< orphan*/ ) ; 

int p_unlink(const char *path)
{
	git_win32_path wpath;

	if (git_win32_path_from_utf8(wpath, path) < 0)
		return -1;

	do_with_retries(unlink_once(wpath), ensure_writable(wpath));
}