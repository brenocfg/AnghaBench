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
struct string_list {int dummy; } ;
struct strbuf {int len; int /*<<< orphan*/ * buf; } ;
typedef  enum discovery_result { ____Placeholder_discovery_result } discovery_result ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEILING_DIRECTORIES_ENVIRONMENT ; 
 char* DEFAULT_GIT_DIR_ENVIRONMENT ; 
 int GIT_DIR_BARE ; 
 int GIT_DIR_DISCOVERED ; 
 int /*<<< orphan*/  GIT_DIR_ENVIRONMENT ; 
 int GIT_DIR_EXPLICIT ; 
 int GIT_DIR_HIT_CEILING ; 
 int GIT_DIR_HIT_MOUNT_POINT ; 
 int GIT_DIR_INVALID_GITFILE ; 
 int /*<<< orphan*/  PATH_SEP ; 
 int READ_GITFILE_ERR_NOT_A_FILE ; 
 int READ_GITFILE_ERR_STAT_FAILED ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  canonicalize_ceiling_entry ; 
 int /*<<< orphan*/  filter_string_list (struct string_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ get_device_or_die (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_env_bool (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_dir_sep (int /*<<< orphan*/ ) ; 
 scalar_t__ is_git_directory (int /*<<< orphan*/ *) ; 
 int longest_ancestor_length (int /*<<< orphan*/ *,struct string_list*) ; 
 int offset_1st_component (int /*<<< orphan*/ *) ; 
 char* read_gitfile_gently (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_split (struct string_list*,char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum discovery_result setup_git_directory_gently_1(struct strbuf *dir,
							  struct strbuf *gitdir,
							  int die_on_error)
{
	const char *env_ceiling_dirs = getenv(CEILING_DIRECTORIES_ENVIRONMENT);
	struct string_list ceiling_dirs = STRING_LIST_INIT_DUP;
	const char *gitdirenv;
	int ceil_offset = -1, min_offset = offset_1st_component(dir->buf);
	dev_t current_device = 0;
	int one_filesystem = 1;

	/*
	 * If GIT_DIR is set explicitly, we're not going
	 * to do any discovery, but we still do repository
	 * validation.
	 */
	gitdirenv = getenv(GIT_DIR_ENVIRONMENT);
	if (gitdirenv) {
		strbuf_addstr(gitdir, gitdirenv);
		return GIT_DIR_EXPLICIT;
	}

	if (env_ceiling_dirs) {
		int empty_entry_found = 0;

		string_list_split(&ceiling_dirs, env_ceiling_dirs, PATH_SEP, -1);
		filter_string_list(&ceiling_dirs, 0,
				   canonicalize_ceiling_entry, &empty_entry_found);
		ceil_offset = longest_ancestor_length(dir->buf, &ceiling_dirs);
		string_list_clear(&ceiling_dirs, 0);
	}

	if (ceil_offset < 0)
		ceil_offset = min_offset - 2;

	if (min_offset && min_offset == dir->len &&
	    !is_dir_sep(dir->buf[min_offset - 1])) {
		strbuf_addch(dir, '/');
		min_offset++;
	}

	/*
	 * Test in the following order (relative to the dir):
	 * - .git (file containing "gitdir: <path>")
	 * - .git/
	 * - ./ (bare)
	 * - ../.git
	 * - ../.git/
	 * - ../ (bare)
	 * - ../../.git
	 *   etc.
	 */
	one_filesystem = !git_env_bool("GIT_DISCOVERY_ACROSS_FILESYSTEM", 0);
	if (one_filesystem)
		current_device = get_device_or_die(dir->buf, NULL, 0);
	for (;;) {
		int offset = dir->len, error_code = 0;

		if (offset > min_offset)
			strbuf_addch(dir, '/');
		strbuf_addstr(dir, DEFAULT_GIT_DIR_ENVIRONMENT);
		gitdirenv = read_gitfile_gently(dir->buf, die_on_error ?
						NULL : &error_code);
		if (!gitdirenv) {
			if (die_on_error ||
			    error_code == READ_GITFILE_ERR_NOT_A_FILE) {
				/* NEEDSWORK: fail if .git is not file nor dir */
				if (is_git_directory(dir->buf))
					gitdirenv = DEFAULT_GIT_DIR_ENVIRONMENT;
			} else if (error_code != READ_GITFILE_ERR_STAT_FAILED)
				return GIT_DIR_INVALID_GITFILE;
		}
		strbuf_setlen(dir, offset);
		if (gitdirenv) {
			strbuf_addstr(gitdir, gitdirenv);
			return GIT_DIR_DISCOVERED;
		}

		if (is_git_directory(dir->buf)) {
			strbuf_addstr(gitdir, ".");
			return GIT_DIR_BARE;
		}

		if (offset <= min_offset)
			return GIT_DIR_HIT_CEILING;

		while (--offset > ceil_offset && !is_dir_sep(dir->buf[offset]))
			; /* continue */
		if (offset <= ceil_offset)
			return GIT_DIR_HIT_CEILING;

		strbuf_setlen(dir, offset > min_offset ?  offset : min_offset);
		if (one_filesystem &&
		    current_device != get_device_or_die(dir->buf, NULL, offset))
			return GIT_DIR_HIT_MOUNT_POINT;
	}
}