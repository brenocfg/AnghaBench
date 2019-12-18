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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GITMODULES_CREATE ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_printf (TYPE_1__*,char*,char const*,char const*) ; 
 int git_config_backend_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_backend_free (int /*<<< orphan*/ *) ; 
 int git_config_backend_set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * open_gitmodules (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_var(git_repository *repo, const char *name, const char *var, const char *val)
{
	git_buf key = GIT_BUF_INIT;
	git_config_backend *mods;
	int error;

	mods = open_gitmodules(repo, GITMODULES_CREATE);
	if (!mods)
		return -1;

	if ((error = git_buf_printf(&key, "submodule.%s.%s", name, var)) < 0)
		goto cleanup;

	if (val)
		error = git_config_backend_set_string(mods, key.ptr, val);
	else
		error = git_config_backend_delete(mods, key.ptr);

	git_buf_dispose(&key);

cleanup:
	git_config_backend_free(mods);
	return error;
}