#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  prune_refs; } ;
typedef  TYPE_1__ git_remote ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 int git_config_get_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_error_clear () ; 

__attribute__((used)) static int lookup_remote_prune_config(git_remote *remote, git_config *config, const char *name)
{
	git_buf buf = GIT_BUF_INIT;
	int error = 0;

	git_buf_printf(&buf, "remote.%s.prune", name);

	if ((error = git_config_get_bool(&remote->prune_refs, config, git_buf_cstr(&buf))) < 0) {
		if (error == GIT_ENOTFOUND) {
			git_error_clear();

			if ((error = git_config_get_bool(&remote->prune_refs, config, "fetch.prune")) < 0) {
				if (error == GIT_ENOTFOUND) {
					git_error_clear();
					error = 0;
				}
			}
		}
	}

	git_buf_dispose(&buf);
	return error;
}