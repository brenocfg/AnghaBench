#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_5__ {TYPE_4__ dir; int /*<<< orphan*/  ign_path; int /*<<< orphan*/  depth; } ;
typedef  TYPE_1__ git_ignores ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_IGNORE_FILE ; 
 scalar_t__ git_buf_joinpath (TYPE_4__*,int /*<<< orphan*/ ,char const*) ; 
 int push_ignore_file (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_ignore__push_dir(git_ignores *ign, const char *dir)
{
	if (git_buf_joinpath(&ign->dir, ign->dir.ptr, dir) < 0)
		return -1;

	ign->depth++;

	return push_ignore_file(
		ign, &ign->ign_path, ign->dir.ptr, GIT_IGNORE_FILE);
}