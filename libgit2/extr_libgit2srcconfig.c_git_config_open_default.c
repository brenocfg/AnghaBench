#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_PROGRAMDATA ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_SYSTEM ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_XDG ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config__global_location (TYPE_1__*) ; 
 int git_config_add_file_ondisk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_find_global (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_find_programdata (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_find_system (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_find_xdg (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_new (int /*<<< orphan*/ **) ; 

int git_config_open_default(git_config **out)
{
	int error;
	git_config *cfg = NULL;
	git_buf buf = GIT_BUF_INIT;

	if ((error = git_config_new(&cfg)) < 0)
		return error;

	if (!git_config_find_global(&buf) || !git_config__global_location(&buf)) {
		error = git_config_add_file_ondisk(cfg, buf.ptr,
			GIT_CONFIG_LEVEL_GLOBAL, NULL, 0);
	}

	if (!error && !git_config_find_xdg(&buf))
		error = git_config_add_file_ondisk(cfg, buf.ptr,
			GIT_CONFIG_LEVEL_XDG, NULL, 0);

	if (!error && !git_config_find_system(&buf))
		error = git_config_add_file_ondisk(cfg, buf.ptr,
			GIT_CONFIG_LEVEL_SYSTEM, NULL, 0);

	if (!error && !git_config_find_programdata(&buf))
		error = git_config_add_file_ondisk(cfg, buf.ptr,
			GIT_CONFIG_LEVEL_PROGRAMDATA, NULL, 0);

	git_buf_dispose(&buf);

	if (error) {
		git_config_free(cfg);
		cfg = NULL;
	}

	*out = cfg;

	return error;
}