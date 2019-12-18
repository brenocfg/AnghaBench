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
struct worktree {int /*<<< orphan*/  id; int /*<<< orphan*/  path; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 unsigned int WT_VALIDATE_WORKTREE_MISSING_OK ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fspathcmp (char*,int /*<<< orphan*/ ) ; 
 int git_common_path (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_absolute_path (int /*<<< orphan*/ ) ; 
 scalar_t__ is_directory (int /*<<< orphan*/ ) ; 
 scalar_t__ is_main_worktree (struct worktree const*) ; 
 int /*<<< orphan*/  read_gitfile_gently (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  real_path (int) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf_gently (struct strbuf*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* xstrdup_or_null (int /*<<< orphan*/ ) ; 

int validate_worktree(const struct worktree *wt, struct strbuf *errmsg,
		      unsigned flags)
{
	struct strbuf wt_path = STRBUF_INIT;
	char *path = NULL;
	int err, ret = -1;

	strbuf_addf(&wt_path, "%s/.git", wt->path);

	if (is_main_worktree(wt)) {
		if (is_directory(wt_path.buf)) {
			ret = 0;
			goto done;
		}
		/*
		 * Main worktree using .git file to point to the
		 * repository would make it impossible to know where
		 * the actual worktree is if this function is executed
		 * from another worktree. No .git file support for now.
		 */
		strbuf_addf_gently(errmsg,
				   _("'%s' at main working tree is not the repository directory"),
				   wt_path.buf);
		goto done;
	}

	/*
	 * Make sure "gitdir" file points to a real .git file and that
	 * file points back here.
	 */
	if (!is_absolute_path(wt->path)) {
		strbuf_addf_gently(errmsg,
				   _("'%s' file does not contain absolute path to the working tree location"),
				   git_common_path("worktrees/%s/gitdir", wt->id));
		goto done;
	}

	if (flags & WT_VALIDATE_WORKTREE_MISSING_OK &&
	    !file_exists(wt->path)) {
		ret = 0;
		goto done;
	}

	if (!file_exists(wt_path.buf)) {
		strbuf_addf_gently(errmsg, _("'%s' does not exist"), wt_path.buf);
		goto done;
	}

	path = xstrdup_or_null(read_gitfile_gently(wt_path.buf, &err));
	if (!path) {
		strbuf_addf_gently(errmsg, _("'%s' is not a .git file, error code %d"),
				   wt_path.buf, err);
		goto done;
	}

	ret = fspathcmp(path, real_path(git_common_path("worktrees/%s", wt->id)));

	if (ret)
		strbuf_addf_gently(errmsg, _("'%s' does not point back to '%s'"),
				   wt->path, git_common_path("worktrees/%s", wt->id));
done:
	free(path);
	strbuf_release(&wt_path);
	return ret;
}