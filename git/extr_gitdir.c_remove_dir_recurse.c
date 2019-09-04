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
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct object_id {int dummy; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ ENOENT ; 
 int REMOVE_DIR_EMPTY_ONLY ; 
 int REMOVE_DIR_KEEP_NESTED_GIT ; 
 int REMOVE_DIR_KEEP_TOPLEVEL ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 scalar_t__ is_dot_or_dotdot (int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolve_gitlink_ref (int /*<<< orphan*/ ,char*,struct object_id*) ; 
 int rmdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_complete (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remove_dir_recurse(struct strbuf *path, int flag, int *kept_up)
{
	DIR *dir;
	struct dirent *e;
	int ret = 0, original_len = path->len, len, kept_down = 0;
	int only_empty = (flag & REMOVE_DIR_EMPTY_ONLY);
	int keep_toplevel = (flag & REMOVE_DIR_KEEP_TOPLEVEL);
	struct object_id submodule_head;

	if ((flag & REMOVE_DIR_KEEP_NESTED_GIT) &&
	    !resolve_gitlink_ref(path->buf, "HEAD", &submodule_head)) {
		/* Do not descend and nuke a nested git work tree. */
		if (kept_up)
			*kept_up = 1;
		return 0;
	}

	flag &= ~REMOVE_DIR_KEEP_TOPLEVEL;
	dir = opendir(path->buf);
	if (!dir) {
		if (errno == ENOENT)
			return keep_toplevel ? -1 : 0;
		else if (errno == EACCES && !keep_toplevel)
			/*
			 * An empty dir could be removable even if it
			 * is unreadable:
			 */
			return rmdir(path->buf);
		else
			return -1;
	}
	strbuf_complete(path, '/');

	len = path->len;
	while ((e = readdir(dir)) != NULL) {
		struct stat st;
		if (is_dot_or_dotdot(e->d_name))
			continue;

		strbuf_setlen(path, len);
		strbuf_addstr(path, e->d_name);
		if (lstat(path->buf, &st)) {
			if (errno == ENOENT)
				/*
				 * file disappeared, which is what we
				 * wanted anyway
				 */
				continue;
			/* fall thru */
		} else if (S_ISDIR(st.st_mode)) {
			if (!remove_dir_recurse(path, flag, &kept_down))
				continue; /* happy */
		} else if (!only_empty &&
			   (!unlink(path->buf) || errno == ENOENT)) {
			continue; /* happy, too */
		}

		/* path too long, stat fails, or non-directory still exists */
		ret = -1;
		break;
	}
	closedir(dir);

	strbuf_setlen(path, original_len);
	if (!ret && !keep_toplevel && !kept_down)
		ret = (!rmdir(path->buf) || errno == ENOENT) ? 0 : -1;
	else if (kept_up)
		/*
		 * report the uplevel that it is not an error that we
		 * did not rmdir() our directory.
		 */
		*kept_up = !ret;
	return ret;
}