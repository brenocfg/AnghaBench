#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_12__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ git_diff_file ;
struct TYPE_13__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;
struct TYPE_11__ {int /*<<< orphan*/  stat_calls; } ;
struct TYPE_14__ {int strategy; TYPE_1__ perfdata; } ;
typedef  TYPE_4__ checkout_data ;

/* Variables and functions */
 int GIT_CHECKOUT_DONT_UPDATE_INDEX ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECKOUT ; 
 int /*<<< orphan*/  GIT_FILEMODE_COMMIT ; 
 scalar_t__ checkout_target_fullpath (TYPE_3__**,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int checkout_update_index (TYPE_4__*,TYPE_2__ const*,struct stat*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ p_stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int checkout_submodule_update_index(
	checkout_data *data,
	const git_diff_file *file)
{
	git_buf *fullpath;
	struct stat st;

	/* update the index unless prevented */
	if ((data->strategy & GIT_CHECKOUT_DONT_UPDATE_INDEX) != 0)
		return 0;

	if (checkout_target_fullpath(&fullpath, data, file->path) < 0)
		return -1;

	data->perfdata.stat_calls++;
	if (p_stat(fullpath->ptr, &st) < 0) {
		git_error_set(
			GIT_ERROR_CHECKOUT, "could not stat submodule %s\n", file->path);
		return GIT_ENOTFOUND;
	}

	st.st_mode = GIT_FILEMODE_COMMIT;

	return checkout_update_index(data, file, &st);
}