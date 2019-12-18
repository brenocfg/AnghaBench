#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; } ;
struct config_include_data {scalar_t__ depth; } ;
struct TYPE_2__ {char* path; char* name; } ;

/* Variables and functions */
 scalar_t__ MAX_INCLUDE_DEPTH ; 
 int /*<<< orphan*/  R_OK ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  access_or_die (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cf ; 
 int config_error_nonbool (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,scalar_t__,char const*,char*) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 char* expand_user_path (char const*,int /*<<< orphan*/ ) ; 
 char* find_last_dir_sep (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int git_config_from_file (int /*<<< orphan*/ ,char const*,struct config_include_data*) ; 
 int /*<<< orphan*/  git_config_include ; 
 char* include_depth_advice ; 
 int /*<<< orphan*/  is_absolute_path (char const*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int handle_path_include(const char *path, struct config_include_data *inc)
{
	int ret = 0;
	struct strbuf buf = STRBUF_INIT;
	char *expanded;

	if (!path)
		return config_error_nonbool("include.path");

	expanded = expand_user_path(path, 0);
	if (!expanded)
		return error(_("could not expand include path '%s'"), path);
	path = expanded;

	/*
	 * Use an absolute path as-is, but interpret relative paths
	 * based on the including config file.
	 */
	if (!is_absolute_path(path)) {
		char *slash;

		if (!cf || !cf->path)
			return error(_("relative config includes must come from files"));

		slash = find_last_dir_sep(cf->path);
		if (slash)
			strbuf_add(&buf, cf->path, slash - cf->path + 1);
		strbuf_addstr(&buf, path);
		path = buf.buf;
	}

	if (!access_or_die(path, R_OK, 0)) {
		if (++inc->depth > MAX_INCLUDE_DEPTH)
			die(_(include_depth_advice), MAX_INCLUDE_DEPTH, path,
			    !cf ? "<unknown>" :
			    cf->name ? cf->name :
			    "the command line");
		ret = git_config_from_file(git_config_include, path, inc);
		inc->depth--;
	}
	strbuf_release(&buf);
	free(expanded);
	return ret;
}