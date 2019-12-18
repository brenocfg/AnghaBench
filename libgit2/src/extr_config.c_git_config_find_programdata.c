#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_FILENAME_PROGRAMDATA ; 
 int GIT_OK ; 
 int /*<<< orphan*/  git_buf_sanitize (TYPE_1__*) ; 
 int git_path_validate_system_file_ownership (int /*<<< orphan*/ ) ; 
 int git_sysdir_find_programdata_file (TYPE_1__*,int /*<<< orphan*/ ) ; 

int git_config_find_programdata(git_buf *path)
{
	int ret;

	git_buf_sanitize(path);
	ret = git_sysdir_find_programdata_file(path,
					       GIT_CONFIG_FILENAME_PROGRAMDATA);
	if (ret != GIT_OK)
		return ret;

	return git_path_validate_system_file_ownership(path->ptr);
}