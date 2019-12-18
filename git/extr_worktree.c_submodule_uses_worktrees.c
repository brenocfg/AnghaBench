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
struct strbuf {int /*<<< orphan*/  buf; scalar_t__ len; } ;
struct repository_format {scalar_t__ version; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 struct repository_format REPOSITORY_FORMAT_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  clear_repository_format (struct repository_format*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_common_dir_noenv (struct strbuf*,char*) ; 
 char* git_pathdup_submodule (char const*,char*,char*) ; 
 scalar_t__ is_dot_or_dotdot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_repository_format (struct repository_format*,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

int submodule_uses_worktrees(const char *path)
{
	char *submodule_gitdir;
	struct strbuf sb = STRBUF_INIT;
	DIR *dir;
	struct dirent *d;
	int ret = 0;
	struct repository_format format = REPOSITORY_FORMAT_INIT;

	submodule_gitdir = git_pathdup_submodule(path, "%s", "");
	if (!submodule_gitdir)
		return 0;

	/* The env would be set for the superproject. */
	get_common_dir_noenv(&sb, submodule_gitdir);
	free(submodule_gitdir);

	/*
	 * The check below is only known to be good for repository format
	 * version 0 at the time of writing this code.
	 */
	strbuf_addstr(&sb, "/config");
	read_repository_format(&format, sb.buf);
	if (format.version != 0) {
		strbuf_release(&sb);
		clear_repository_format(&format);
		return 1;
	}
	clear_repository_format(&format);

	/* Replace config by worktrees. */
	strbuf_setlen(&sb, sb.len - strlen("config"));
	strbuf_addstr(&sb, "worktrees");

	/* See if there is any file inside the worktrees directory. */
	dir = opendir(sb.buf);
	strbuf_release(&sb);

	if (!dir)
		return 0;

	while ((d = readdir(dir)) != NULL) {
		if (is_dot_or_dotdot(d->d_name))
			continue;

		ret = 1;
		break;
	}
	closedir(dir);
	return ret;
}