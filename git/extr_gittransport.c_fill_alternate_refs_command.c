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
struct child_process {int use_shell; int git_cmd; int out; int /*<<< orphan*/  env; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  argv_array_split (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_config_get_value (char*,char const**) ; 
 int /*<<< orphan*/  local_repo_env ; 

__attribute__((used)) static void fill_alternate_refs_command(struct child_process *cmd,
					const char *repo_path)
{
	const char *value;

	if (!git_config_get_value("core.alternateRefsCommand", &value)) {
		cmd->use_shell = 1;

		argv_array_push(&cmd->args, value);
		argv_array_push(&cmd->args, repo_path);
	} else {
		cmd->git_cmd = 1;

		argv_array_pushf(&cmd->args, "--git-dir=%s", repo_path);
		argv_array_push(&cmd->args, "for-each-ref");
		argv_array_push(&cmd->args, "--format=%(objectname)");

		if (!git_config_get_value("core.alternateRefsPrefixes", &value)) {
			argv_array_push(&cmd->args, "--");
			argv_array_split(&cmd->args, value);
		}
	}

	cmd->env = local_repo_env;
	cmd->out = -1;
}