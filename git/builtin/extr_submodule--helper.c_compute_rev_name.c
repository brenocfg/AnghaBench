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
struct strbuf {int dummy; } ;
struct child_process {char const* dir; int git_cmd; int no_stderr; int /*<<< orphan*/  args; int /*<<< orphan*/  env_array; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  argv_array_pushv (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  capture_command (struct child_process*,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_submodule_repo_env (int /*<<< orphan*/ *) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_strip_suffix (struct strbuf*,char*) ; 

__attribute__((used)) static char *compute_rev_name(const char *sub_path, const char* object_id)
{
	struct strbuf sb = STRBUF_INIT;
	const char ***d;

	static const char *describe_bare[] = { NULL };

	static const char *describe_tags[] = { "--tags", NULL };

	static const char *describe_contains[] = { "--contains", NULL };

	static const char *describe_all_always[] = { "--all", "--always", NULL };

	static const char **describe_argv[] = { describe_bare, describe_tags,
						describe_contains,
						describe_all_always, NULL };

	for (d = describe_argv; *d; d++) {
		struct child_process cp = CHILD_PROCESS_INIT;
		prepare_submodule_repo_env(&cp.env_array);
		cp.dir = sub_path;
		cp.git_cmd = 1;
		cp.no_stderr = 1;

		argv_array_push(&cp.args, "describe");
		argv_array_pushv(&cp.args, *d);
		argv_array_push(&cp.args, object_id);

		if (!capture_command(&cp, &sb, 0)) {
			strbuf_strip_suffix(&sb, "\n");
			return strbuf_detach(&sb, NULL);
		}
	}

	strbuf_release(&sb);
	return NULL;
}