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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ git_path_resolve_relative (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_path_apply_relative(git_buf *target, const char *relpath)
{
	return git_buf_joinpath(target, git_buf_cstr(target), relpath) ||
	    git_path_resolve_relative(target, 0);
}