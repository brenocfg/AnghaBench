#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  mkdir_flags; int /*<<< orphan*/  dirmode; int /*<<< orphan*/  to_root; scalar_t__ from_prefix; } ;
typedef  TYPE_2__ cp_r_info ;

/* Variables and functions */
 int GIT_CPDIR_CHMOD_DIRS ; 
 int GIT_CPDIR__MKDIR_DONE_FOR_TO_ROOT ; 
 int /*<<< orphan*/  GIT_MKDIR_CHMOD ; 
 int git_futils_mkdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_futils_mkdir_relative (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _cp_r_mkdir(cp_r_info *info, git_buf *from)
{
	int error = 0;

	/* create root directory the first time we need to create a directory */
	if ((info->flags & GIT_CPDIR__MKDIR_DONE_FOR_TO_ROOT) == 0) {
		error = git_futils_mkdir(
			info->to_root, info->dirmode,
			(info->flags & GIT_CPDIR_CHMOD_DIRS) ? GIT_MKDIR_CHMOD : 0);

		info->flags |= GIT_CPDIR__MKDIR_DONE_FOR_TO_ROOT;
	}

	/* create directory with root as base to prevent excess chmods */
	if (!error)
		error = git_futils_mkdir_relative(
			from->ptr + info->from_prefix, info->to_root,
			info->dirmode, info->mkdir_flags, NULL);

	return error;
}