#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct untracked_cache_dir {int recurse; } ;
struct pathspec {scalar_t__ nr; } ;
struct TYPE_8__ {int /*<<< orphan*/  oid; } ;
struct TYPE_7__ {int /*<<< orphan*/  oid; } ;
struct dir_struct {int flags; scalar_t__ exclude_per_dir; TYPE_3__ ss_excludes_file; TYPE_4__* untracked; TYPE_2__ ss_info_exclude; TYPE_1__* exclude_list_group; scalar_t__ unmanaged_exclude_files; } ;
struct TYPE_9__ {int dir_flags; scalar_t__ exclude_per_dir; TYPE_3__ ss_excludes_file; TYPE_2__ ss_info_exclude; struct untracked_cache_dir* root; } ;
struct TYPE_6__ {scalar_t__ nr; } ;

/* Variables and functions */
 int DIR_COLLECT_IGNORED ; 
 int DIR_SHOW_IGNORED ; 
 int DIR_SHOW_IGNORED_TOO ; 
 int DIR_SHOW_OTHER_DIRECTORIES ; 
 size_t EXC_CMDL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int git_env_bool (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ident_in_untracked (TYPE_4__*) ; 
 int /*<<< orphan*/  invalidate_gitignore (TYPE_4__*,struct untracked_cache_dir*) ; 
 int /*<<< orphan*/  memset (struct untracked_cache_dir*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 
 struct untracked_cache_dir* xmalloc (int const) ; 

__attribute__((used)) static struct untracked_cache_dir *validate_untracked_cache(struct dir_struct *dir,
						      int base_len,
						      const struct pathspec *pathspec)
{
	struct untracked_cache_dir *root;
	static int untracked_cache_disabled = -1;

	if (!dir->untracked)
		return NULL;
	if (untracked_cache_disabled < 0)
		untracked_cache_disabled = git_env_bool("GIT_DISABLE_UNTRACKED_CACHE", 0);
	if (untracked_cache_disabled)
		return NULL;

	/*
	 * We only support $GIT_DIR/info/exclude and core.excludesfile
	 * as the global ignore rule files. Any other additions
	 * (e.g. from command line) invalidate the cache. This
	 * condition also catches running setup_standard_excludes()
	 * before setting dir->untracked!
	 */
	if (dir->unmanaged_exclude_files)
		return NULL;

	/*
	 * Optimize for the main use case only: whole-tree git
	 * status. More work involved in treat_leading_path() if we
	 * use cache on just a subset of the worktree. pathspec
	 * support could make the matter even worse.
	 */
	if (base_len || (pathspec && pathspec->nr))
		return NULL;

	/* Different set of flags may produce different results */
	if (dir->flags != dir->untracked->dir_flags ||
	    /*
	     * See treat_directory(), case index_nonexistent. Without
	     * this flag, we may need to also cache .git file content
	     * for the resolve_gitlink_ref() call, which we don't.
	     */
	    !(dir->flags & DIR_SHOW_OTHER_DIRECTORIES) ||
	    /* We don't support collecting ignore files */
	    (dir->flags & (DIR_SHOW_IGNORED | DIR_SHOW_IGNORED_TOO |
			   DIR_COLLECT_IGNORED)))
		return NULL;

	/*
	 * If we use .gitignore in the cache and now you change it to
	 * .gitexclude, everything will go wrong.
	 */
	if (dir->exclude_per_dir != dir->untracked->exclude_per_dir &&
	    strcmp(dir->exclude_per_dir, dir->untracked->exclude_per_dir))
		return NULL;

	/*
	 * EXC_CMDL is not considered in the cache. If people set it,
	 * skip the cache.
	 */
	if (dir->exclude_list_group[EXC_CMDL].nr)
		return NULL;

	if (!ident_in_untracked(dir->untracked)) {
		warning(_("untracked cache is disabled on this system or location"));
		return NULL;
	}

	if (!dir->untracked->root) {
		const int len = sizeof(*dir->untracked->root);
		dir->untracked->root = xmalloc(len);
		memset(dir->untracked->root, 0, len);
	}

	/* Validate $GIT_DIR/info/exclude and core.excludesfile */
	root = dir->untracked->root;
	if (!oideq(&dir->ss_info_exclude.oid,
		   &dir->untracked->ss_info_exclude.oid)) {
		invalidate_gitignore(dir->untracked, root);
		dir->untracked->ss_info_exclude = dir->ss_info_exclude;
	}
	if (!oideq(&dir->ss_excludes_file.oid,
		   &dir->untracked->ss_excludes_file.oid)) {
		invalidate_gitignore(dir->untracked, root);
		dir->untracked->ss_excludes_file = dir->ss_excludes_file;
	}

	/* Make sure this directory is not dropped out at saving phase */
	root->recurse = 1;
	return root;
}