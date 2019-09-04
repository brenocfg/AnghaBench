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
struct submodule {char const* name; char* url; } ;
struct strbuf {scalar_t__ len; } ;
struct child_process {int git_cmd; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 unsigned int OPT_FORCE ; 
 unsigned int OPT_QUIET ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  capture_command (struct child_process*,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_submodule_displaypath (char const*,char const*) ; 
 int /*<<< orphan*/  git_config_rename_section_in_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_directory (char const*) ; 
 scalar_t__ mkdir (char const*,int) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  printf (char const*,char const*,...) ; 
 int /*<<< orphan*/  remove_dir_recursively (struct strbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ run_command (struct child_process*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 struct submodule* submodule_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  submodule_unset_core_worktree (struct submodule const*) ; 
 int /*<<< orphan*/  the_repository ; 
 char* xstrfmt (char*,char const*) ; 

__attribute__((used)) static void deinit_submodule(const char *path, const char *prefix,
			     unsigned int flags)
{
	const struct submodule *sub;
	char *displaypath = NULL;
	struct child_process cp_config = CHILD_PROCESS_INIT;
	struct strbuf sb_config = STRBUF_INIT;
	char *sub_git_dir = xstrfmt("%s/.git", path);

	sub = submodule_from_path(the_repository, &null_oid, path);

	if (!sub || !sub->name)
		goto cleanup;

	displaypath = get_submodule_displaypath(path, prefix);

	/* remove the submodule work tree (unless the user already did it) */
	if (is_directory(path)) {
		struct strbuf sb_rm = STRBUF_INIT;
		const char *format;

		/*
		 * protect submodules containing a .git directory
		 * NEEDSWORK: instead of dying, automatically call
		 * absorbgitdirs and (possibly) warn.
		 */
		if (is_directory(sub_git_dir))
			die(_("Submodule work tree '%s' contains a .git "
			      "directory (use 'rm -rf' if you really want "
			      "to remove it including all of its history)"),
			    displaypath);

		if (!(flags & OPT_FORCE)) {
			struct child_process cp_rm = CHILD_PROCESS_INIT;
			cp_rm.git_cmd = 1;
			argv_array_pushl(&cp_rm.args, "rm", "-qn",
					 path, NULL);

			if (run_command(&cp_rm))
				die(_("Submodule work tree '%s' contains local "
				      "modifications; use '-f' to discard them"),
				      displaypath);
		}

		strbuf_addstr(&sb_rm, path);

		if (!remove_dir_recursively(&sb_rm, 0))
			format = _("Cleared directory '%s'\n");
		else
			format = _("Could not remove submodule work tree '%s'\n");

		if (!(flags & OPT_QUIET))
			printf(format, displaypath);

		submodule_unset_core_worktree(sub);

		strbuf_release(&sb_rm);
	}

	if (mkdir(path, 0777))
		printf(_("could not create empty submodule directory %s"),
		      displaypath);

	cp_config.git_cmd = 1;
	argv_array_pushl(&cp_config.args, "config", "--get-regexp", NULL);
	argv_array_pushf(&cp_config.args, "submodule.%s\\.", sub->name);

	/* remove the .git/config entries (unless the user already did it) */
	if (!capture_command(&cp_config, &sb_config, 0) && sb_config.len) {
		char *sub_key = xstrfmt("submodule.%s", sub->name);
		/*
		 * remove the whole section so we have a clean state when
		 * the user later decides to init this submodule again
		 */
		git_config_rename_section_in_file(NULL, sub_key, NULL);
		if (!(flags & OPT_QUIET))
			printf(_("Submodule '%s' (%s) unregistered for path '%s'\n"),
				 sub->name, sub->url, displaypath);
		free(sub_key);
	}

cleanup:
	free(displaypath);
	free(sub_git_dir);
	strbuf_release(&sb_config);
}