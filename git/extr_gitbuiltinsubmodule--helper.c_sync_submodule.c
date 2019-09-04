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
struct submodule {char* url; char* name; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct child_process {int git_cmd; char const* dir; int /*<<< orphan*/  args; int /*<<< orphan*/  env_array; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 unsigned int OPT_QUIET ; 
 unsigned int OPT_RECURSIVE ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,...) ; 
 scalar_t__ capture_command (struct child_process*,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_default_remote () ; 
 char* get_submodule_displaypath (char const*,char const*) ; 
 char* get_up_path (char const*) ; 
 scalar_t__ git_config_get_string (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ git_config_set_gently (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_config_set_in_file_gently (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  is_submodule_active (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  is_submodule_populated_gently (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  prepare_submodule_repo_env (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* relative_url (char*,char*,char*) ; 
 scalar_t__ run_command (struct child_process*) ; 
 scalar_t__ starts_with_dot_dot_slash (char*) ; 
 scalar_t__ starts_with_dot_slash (char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_strip_suffix (struct strbuf*,char*) ; 
 struct submodule* submodule_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  submodule_to_gitdir (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  the_repository ; 
 char* xgetcwd () ; 
 char* xstrdup (char*) ; 
 char* xstrfmt (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sync_submodule(const char *path, const char *prefix,
			   unsigned int flags)
{
	const struct submodule *sub;
	char *remote_key = NULL;
	char *sub_origin_url, *super_config_url, *displaypath;
	struct strbuf sb = STRBUF_INIT;
	struct child_process cp = CHILD_PROCESS_INIT;
	char *sub_config_path = NULL;

	if (!is_submodule_active(the_repository, path))
		return;

	sub = submodule_from_path(the_repository, &null_oid, path);

	if (sub && sub->url) {
		if (starts_with_dot_dot_slash(sub->url) ||
		    starts_with_dot_slash(sub->url)) {
			char *remote_url, *up_path;
			char *remote = get_default_remote();
			strbuf_addf(&sb, "remote.%s.url", remote);

			if (git_config_get_string(sb.buf, &remote_url))
				remote_url = xgetcwd();

			up_path = get_up_path(path);
			sub_origin_url = relative_url(remote_url, sub->url, up_path);
			super_config_url = relative_url(remote_url, sub->url, NULL);

			free(remote);
			free(up_path);
			free(remote_url);
		} else {
			sub_origin_url = xstrdup(sub->url);
			super_config_url = xstrdup(sub->url);
		}
	} else {
		sub_origin_url = xstrdup("");
		super_config_url = xstrdup("");
	}

	displaypath = get_submodule_displaypath(path, prefix);

	if (!(flags & OPT_QUIET))
		printf(_("Synchronizing submodule url for '%s'\n"),
			 displaypath);

	strbuf_reset(&sb);
	strbuf_addf(&sb, "submodule.%s.url", sub->name);
	if (git_config_set_gently(sb.buf, super_config_url))
		die(_("failed to register url for submodule path '%s'"),
		      displaypath);

	if (!is_submodule_populated_gently(path, NULL))
		goto cleanup;

	prepare_submodule_repo_env(&cp.env_array);
	cp.git_cmd = 1;
	cp.dir = path;
	argv_array_pushl(&cp.args, "submodule--helper",
			 "print-default-remote", NULL);

	strbuf_reset(&sb);
	if (capture_command(&cp, &sb, 0))
		die(_("failed to get the default remote for submodule '%s'"),
		      path);

	strbuf_strip_suffix(&sb, "\n");
	remote_key = xstrfmt("remote.%s.url", sb.buf);

	strbuf_reset(&sb);
	submodule_to_gitdir(&sb, path);
	strbuf_addstr(&sb, "/config");

	if (git_config_set_in_file_gently(sb.buf, remote_key, sub_origin_url))
		die(_("failed to update remote for submodule '%s'"),
		      path);

	if (flags & OPT_RECURSIVE) {
		struct child_process cpr = CHILD_PROCESS_INIT;

		cpr.git_cmd = 1;
		cpr.dir = path;
		prepare_submodule_repo_env(&cpr.env_array);

		argv_array_push(&cpr.args, "--super-prefix");
		argv_array_pushf(&cpr.args, "%s/", displaypath);
		argv_array_pushl(&cpr.args, "submodule--helper", "sync",
				 "--recursive", NULL);

		if (flags & OPT_QUIET)
			argv_array_push(&cpr.args, "--quiet");

		if (run_command(&cpr))
			die(_("failed to recurse into submodule '%s'"),
			      path);
	}

cleanup:
	free(super_config_url);
	free(sub_origin_url);
	strbuf_release(&sb);
	free(remote_key);
	free(displaypath);
	free(sub_config_path);
}