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
struct string_list {int nr; TYPE_1__* items; } ;
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int REMOVE_DIR_KEEP_NESTED_GIT ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 char* _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 scalar_t__ is_dot_or_dotdot (int /*<<< orphan*/ ) ; 
 scalar_t__ is_nonbare_repository_dir (struct strbuf*) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  msg_remove ; 
 int /*<<< orphan*/  msg_skip_git_dir ; 
 int /*<<< orphan*/  msg_warn_lstat_failed ; 
 int /*<<< orphan*/  msg_warn_remove_failed ; 
 int /*<<< orphan*/  msg_would_remove ; 
 int /*<<< orphan*/  msg_would_skip_git_dir ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote_path_relative (int /*<<< orphan*/ ,char const*,struct strbuf*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int rmdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_complete (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning_errno (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remove_dirs(struct strbuf *path, const char *prefix, int force_flag,
		int dry_run, int quiet, int *dir_gone)
{
	DIR *dir;
	struct strbuf quoted = STRBUF_INIT;
	struct dirent *e;
	int res = 0, ret = 0, gone = 1, original_len = path->len, len;
	struct string_list dels = STRING_LIST_INIT_DUP;

	*dir_gone = 1;

	if ((force_flag & REMOVE_DIR_KEEP_NESTED_GIT) &&
	    is_nonbare_repository_dir(path)) {
		if (!quiet) {
			quote_path_relative(path->buf, prefix, &quoted);
			printf(dry_run ?  _(msg_would_skip_git_dir) : _(msg_skip_git_dir),
					quoted.buf);
		}

		*dir_gone = 0;
		goto out;
	}

	dir = opendir(path->buf);
	if (!dir) {
		/* an empty dir could be removed even if it is unreadble */
		res = dry_run ? 0 : rmdir(path->buf);
		if (res) {
			int saved_errno = errno;
			quote_path_relative(path->buf, prefix, &quoted);
			errno = saved_errno;
			warning_errno(_(msg_warn_remove_failed), quoted.buf);
			*dir_gone = 0;
		}
		ret = res;
		goto out;
	}

	strbuf_complete(path, '/');

	len = path->len;
	while ((e = readdir(dir)) != NULL) {
		struct stat st;
		if (is_dot_or_dotdot(e->d_name))
			continue;

		strbuf_setlen(path, len);
		strbuf_addstr(path, e->d_name);
		if (lstat(path->buf, &st))
			warning_errno(_(msg_warn_lstat_failed), path->buf);
		else if (S_ISDIR(st.st_mode)) {
			if (remove_dirs(path, prefix, force_flag, dry_run, quiet, &gone))
				ret = 1;
			if (gone) {
				quote_path_relative(path->buf, prefix, &quoted);
				string_list_append(&dels, quoted.buf);
			} else
				*dir_gone = 0;
			continue;
		} else {
			res = dry_run ? 0 : unlink(path->buf);
			if (!res) {
				quote_path_relative(path->buf, prefix, &quoted);
				string_list_append(&dels, quoted.buf);
			} else {
				int saved_errno = errno;
				quote_path_relative(path->buf, prefix, &quoted);
				errno = saved_errno;
				warning_errno(_(msg_warn_remove_failed), quoted.buf);
				*dir_gone = 0;
				ret = 1;
			}
			continue;
		}

		/* path too long, stat fails, or non-directory still exists */
		*dir_gone = 0;
		ret = 1;
		break;
	}
	closedir(dir);

	strbuf_setlen(path, original_len);

	if (*dir_gone) {
		res = dry_run ? 0 : rmdir(path->buf);
		if (!res)
			*dir_gone = 1;
		else {
			int saved_errno = errno;
			quote_path_relative(path->buf, prefix, &quoted);
			errno = saved_errno;
			warning_errno(_(msg_warn_remove_failed), quoted.buf);
			*dir_gone = 0;
			ret = 1;
		}
	}

	if (!*dir_gone && !quiet) {
		int i;
		for (i = 0; i < dels.nr; i++)
			printf(dry_run ?  _(msg_would_remove) : _(msg_remove), dels.items[i].string);
	}
out:
	strbuf_release(&quoted);
	string_list_clear(&dels, 0);
	return ret;
}