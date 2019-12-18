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
struct submodule {char* name; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct child_process {int use_shell; char const* dir; int git_cmd; int /*<<< orphan*/  args; int /*<<< orphan*/  env_array; } ;
struct cb_foreach {int argc; scalar_t__* argv; scalar_t__ quiet; scalar_t__ recursive; int /*<<< orphan*/  prefix; } ;
struct cache_entry {char* name; struct object_id oid; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  argv_array_pushv (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_submodule_displaypath (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_submodule_populated_gently (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  null_oid ; 
 char* oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  prepare_submodule_repo_env (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ run_command (struct child_process*) ; 
 int /*<<< orphan*/  sq_quote_buf (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 struct submodule* submodule_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  the_repository ; 
 char* xgetcwd () ; 

__attribute__((used)) static void runcommand_in_submodule_cb(const struct cache_entry *list_item,
				       void *cb_data)
{
	struct cb_foreach *info = cb_data;
	const char *path = list_item->name;
	const struct object_id *ce_oid = &list_item->oid;

	const struct submodule *sub;
	struct child_process cp = CHILD_PROCESS_INIT;
	char *displaypath;

	displaypath = get_submodule_displaypath(path, info->prefix);

	sub = submodule_from_path(the_repository, &null_oid, path);

	if (!sub)
		die(_("No url found for submodule path '%s' in .gitmodules"),
			displaypath);

	if (!is_submodule_populated_gently(path, NULL))
		goto cleanup;

	prepare_submodule_repo_env(&cp.env_array);

	/*
	 * For the purpose of executing <command> in the submodule,
	 * separate shell is used for the purpose of running the
	 * child process.
	 */
	cp.use_shell = 1;
	cp.dir = path;

	/*
	 * NEEDSWORK: the command currently has access to the variables $name,
	 * $sm_path, $displaypath, $sha1 and $toplevel only when the command
	 * contains a single argument. This is done for maintaining a faithful
	 * translation from shell script.
	 */
	if (info->argc == 1) {
		char *toplevel = xgetcwd();
		struct strbuf sb = STRBUF_INIT;

		argv_array_pushf(&cp.env_array, "name=%s", sub->name);
		argv_array_pushf(&cp.env_array, "sm_path=%s", path);
		argv_array_pushf(&cp.env_array, "displaypath=%s", displaypath);
		argv_array_pushf(&cp.env_array, "sha1=%s",
				oid_to_hex(ce_oid));
		argv_array_pushf(&cp.env_array, "toplevel=%s", toplevel);

		/*
		 * Since the path variable was accessible from the script
		 * before porting, it is also made available after porting.
		 * The environment variable "PATH" has a very special purpose
		 * on windows. And since environment variables are
		 * case-insensitive in windows, it interferes with the
		 * existing PATH variable. Hence, to avoid that, we expose
		 * path via the args argv_array and not via env_array.
		 */
		sq_quote_buf(&sb, path);
		argv_array_pushf(&cp.args, "path=%s; %s",
				 sb.buf, info->argv[0]);
		strbuf_release(&sb);
		free(toplevel);
	} else {
		argv_array_pushv(&cp.args, info->argv);
	}

	if (!info->quiet)
		printf(_("Entering '%s'\n"), displaypath);

	if (info->argv[0] && run_command(&cp))
		die(_("run_command returned non-zero status for %s\n."),
			displaypath);

	if (info->recursive) {
		struct child_process cpr = CHILD_PROCESS_INIT;

		cpr.git_cmd = 1;
		cpr.dir = path;
		prepare_submodule_repo_env(&cpr.env_array);

		argv_array_pushl(&cpr.args, "--super-prefix", NULL);
		argv_array_pushf(&cpr.args, "%s/", displaypath);
		argv_array_pushl(&cpr.args, "submodule--helper", "foreach", "--recursive",
				NULL);

		if (info->quiet)
			argv_array_push(&cpr.args, "--quiet");

		argv_array_push(&cpr.args, "--");
		argv_array_pushv(&cpr.args, info->argv);

		if (run_command(&cpr))
			die(_("run_command returned non-zero status while "
				"recursing in the nested submodules of %s\n."),
				displaypath);
	}

cleanup:
	free(displaypath);
}