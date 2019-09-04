#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wtopts ;
struct TYPE_36__ {scalar_t__ ref; scalar_t__ lock; } ;
typedef  TYPE_2__ git_worktree_add_options ;
typedef  int /*<<< orphan*/  git_worktree ;
struct TYPE_37__ {char const* commondir; } ;
typedef  TYPE_3__ git_repository ;
struct TYPE_35__ {int /*<<< orphan*/  oid; } ;
struct TYPE_38__ {TYPE_1__ target; } ;
typedef  TYPE_4__ git_reference ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_39__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_5__ git_checkout_options ;
struct TYPE_40__ {char const* ptr; } ;
typedef  TYPE_6__ git_buf ;

/* Variables and functions */
 TYPE_6__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_5__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (TYPE_2__ const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GIT_ERROR_WORKTREE ; 
 int /*<<< orphan*/  GIT_MKDIR_EXCL ; 
 TYPE_2__ GIT_WORKTREE_ADD_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_WORKTREE_ADD_OPTIONS_VERSION ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int git_branch_create (TYPE_4__**,TYPE_3__*,char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ git_branch_is_checked_out (scalar_t__) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_6__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_6__*) ; 
 int git_buf_joinpath (TYPE_6__*,char const*,char const*) ; 
 int git_buf_printf (TYPE_6__*,char*,char const*) ; 
 int git_buf_putc (TYPE_6__*,char) ; 
 int git_checkout_head (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_futils_mkdir (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_exists (char const*) ; 
 int git_path_prettify_dir (TYPE_6__*,char const*,int /*<<< orphan*/ *) ; 
 int git_reference_dup (TYPE_4__**,scalar_t__) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_4__*) ; 
 int /*<<< orphan*/  git_reference_is_branch (scalar_t__) ; 
 int /*<<< orphan*/  git_reference_name (TYPE_4__*) ; 
 int git_repository_create_head (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (TYPE_3__*) ; 
 int git_repository_head (TYPE_4__**,TYPE_3__*) ; 
 int git_repository_open (TYPE_3__**,char const*) ; 
 int git_worktree_lookup (int /*<<< orphan*/ **,TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int p_creat (char const*,int) ; 
 int write_wtfile (char const*,char*,TYPE_6__*) ; 

int git_worktree_add(git_worktree **out, git_repository *repo,
	const char *name, const char *worktree,
	const git_worktree_add_options *opts)
{
	git_buf gitdir = GIT_BUF_INIT, wddir = GIT_BUF_INIT, buf = GIT_BUF_INIT;
	git_reference *ref = NULL, *head = NULL;
	git_commit *commit = NULL;
	git_repository *wt = NULL;
	git_checkout_options coopts = GIT_CHECKOUT_OPTIONS_INIT;
	git_worktree_add_options wtopts = GIT_WORKTREE_ADD_OPTIONS_INIT;
	int err;

	GIT_ERROR_CHECK_VERSION(
		opts, GIT_WORKTREE_ADD_OPTIONS_VERSION, "git_worktree_add_options");

	if (opts)
		memcpy(&wtopts, opts, sizeof(wtopts));

	assert(out && repo && name && worktree);

	*out = NULL;

	if (wtopts.ref) {
		if (!git_reference_is_branch(wtopts.ref)) {
			git_error_set(GIT_ERROR_WORKTREE, "reference is not a branch");
			err = -1;
			goto out;
		}

		if (git_branch_is_checked_out(wtopts.ref)) {
			git_error_set(GIT_ERROR_WORKTREE, "reference is already checked out");
			err = -1;
			goto out;
		}
	}

	/* Create gitdir directory ".git/worktrees/<name>" */
	if ((err = git_buf_joinpath(&gitdir, repo->commondir, "worktrees")) < 0)
		goto out;
	if (!git_path_exists(gitdir.ptr))
		if ((err = git_futils_mkdir(gitdir.ptr, 0755, GIT_MKDIR_EXCL)) < 0)
			goto out;
	if ((err = git_buf_joinpath(&gitdir, gitdir.ptr, name)) < 0)
		goto out;
	if ((err = git_futils_mkdir(gitdir.ptr, 0755, GIT_MKDIR_EXCL)) < 0)
		goto out;
	if ((err = git_path_prettify_dir(&gitdir, gitdir.ptr, NULL)) < 0)
		goto out;

	/* Create worktree work dir */
	if ((err = git_futils_mkdir(worktree, 0755, GIT_MKDIR_EXCL)) < 0)
		goto out;
	if ((err = git_path_prettify_dir(&wddir, worktree, NULL)) < 0)
		goto out;

	if (wtopts.lock) {
		int fd;

		if ((err = git_buf_joinpath(&buf, gitdir.ptr, "locked")) < 0)
			goto out;

		if ((fd = p_creat(buf.ptr, 0644)) < 0) {
			err = fd;
			goto out;
		}

		p_close(fd);
		git_buf_clear(&buf);
	}

	/* Create worktree .git file */
	if ((err = git_buf_printf(&buf, "gitdir: %s\n", gitdir.ptr)) < 0)
		goto out;
	if ((err = write_wtfile(wddir.ptr, ".git", &buf)) < 0)
		goto out;

	/* Create gitdir files */
	if ((err = git_path_prettify_dir(&buf, repo->commondir, NULL) < 0)
	    || (err = git_buf_putc(&buf, '\n')) < 0
	    || (err = write_wtfile(gitdir.ptr, "commondir", &buf)) < 0)
		goto out;
	if ((err = git_buf_joinpath(&buf, wddir.ptr, ".git")) < 0
	    || (err = git_buf_putc(&buf, '\n')) < 0
	    || (err = write_wtfile(gitdir.ptr, "gitdir", &buf)) < 0)
		goto out;

	/* Set up worktree reference */
	if (wtopts.ref) {
		if ((err = git_reference_dup(&ref, wtopts.ref)) < 0)
			goto out;
	} else {
		if ((err = git_repository_head(&head, repo)) < 0)
			goto out;
		if ((err = git_commit_lookup(&commit, repo, &head->target.oid)) < 0)
			goto out;
		if ((err = git_branch_create(&ref, repo, name, commit, false)) < 0)
			goto out;
	}

	/* Set worktree's HEAD */
	if ((err = git_repository_create_head(gitdir.ptr, git_reference_name(ref))) < 0)
		goto out;
	if ((err = git_repository_open(&wt, wddir.ptr)) < 0)
		goto out;

	/* Checkout worktree's HEAD */
	coopts.checkout_strategy = GIT_CHECKOUT_FORCE;
	if ((err = git_checkout_head(wt, &coopts)) < 0)
		goto out;

	/* Load result */
	if ((err = git_worktree_lookup(out, repo, name)) < 0)
		goto out;

out:
	git_buf_dispose(&gitdir);
	git_buf_dispose(&wddir);
	git_buf_dispose(&buf);
	git_reference_free(ref);
	git_reference_free(head);
	git_commit_free(commit);
	git_repository_free(wt);

	return err;
}