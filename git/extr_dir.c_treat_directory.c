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
struct untracked_cache_dir {int dummy; } ;
struct strbuf {int dummy; } ;
struct pathspec {int dummy; } ;
struct index_state {int dummy; } ;
struct dir_struct {int flags; int /*<<< orphan*/  untracked; } ;
typedef  enum path_treatment { ____Placeholder_path_treatment } path_treatment ;

/* Variables and functions */
 int DIR_HIDE_EMPTY_DIRECTORIES ; 
 int DIR_NO_GITLINKS ; 
 int DIR_SHOW_IGNORED_TOO ; 
 int DIR_SHOW_IGNORED_TOO_MODE_MATCHING ; 
 int DIR_SHOW_OTHER_DIRECTORIES ; 
 int DIR_SKIP_NESTED_GIT ; 
 struct strbuf STRBUF_INIT ; 
 int directory_exists_in_index (struct index_state*,char const*,int) ; 
#define  index_directory 130 
#define  index_gitdir 129 
#define  index_nonexistent 128 
 int is_nonbare_repository_dir (struct strbuf*) ; 
 struct untracked_cache_dir* lookup_untracked (int /*<<< orphan*/ ,struct untracked_cache_dir*,char const*,int) ; 
 int path_excluded ; 
 int path_none ; 
 int path_recurse ; 
 int path_untracked ; 
 int read_directory_recursive (struct dir_struct*,struct index_state*,char const*,int,struct untracked_cache_dir*,int,int,struct pathspec const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static enum path_treatment treat_directory(struct dir_struct *dir,
	struct index_state *istate,
	struct untracked_cache_dir *untracked,
	const char *dirname, int len, int baselen, int exclude,
	const struct pathspec *pathspec)
{
	/* The "len-1" is to strip the final '/' */
	switch (directory_exists_in_index(istate, dirname, len-1)) {
	case index_directory:
		return path_recurse;

	case index_gitdir:
		return path_none;

	case index_nonexistent:
		if (dir->flags & DIR_SKIP_NESTED_GIT) {
			int nested_repo;
			struct strbuf sb = STRBUF_INIT;
			strbuf_addstr(&sb, dirname);
			nested_repo = is_nonbare_repository_dir(&sb);
			strbuf_release(&sb);
			if (nested_repo)
				return path_none;
		}

		if (dir->flags & DIR_SHOW_OTHER_DIRECTORIES)
			break;
		if (exclude &&
			(dir->flags & DIR_SHOW_IGNORED_TOO) &&
			(dir->flags & DIR_SHOW_IGNORED_TOO_MODE_MATCHING)) {

			/*
			 * This is an excluded directory and we are
			 * showing ignored paths that match an exclude
			 * pattern.  (e.g. show directory as ignored
			 * only if it matches an exclude pattern).
			 * This path will either be 'path_excluded`
			 * (if we are showing empty directories or if
			 * the directory is not empty), or will be
			 * 'path_none' (empty directory, and we are
			 * not showing empty directories).
			 */
			if (!(dir->flags & DIR_HIDE_EMPTY_DIRECTORIES))
				return path_excluded;

			if (read_directory_recursive(dir, istate, dirname, len,
						     untracked, 1, 1, pathspec) == path_excluded)
				return path_excluded;

			return path_none;
		}
		if (!(dir->flags & DIR_NO_GITLINKS)) {
			struct strbuf sb = STRBUF_INIT;
			strbuf_addstr(&sb, dirname);
			if (is_nonbare_repository_dir(&sb))
				return exclude ? path_excluded : path_untracked;
			strbuf_release(&sb);
		}
		return path_recurse;
	}

	/* This is the "show_other_directories" case */

	if (!(dir->flags & DIR_HIDE_EMPTY_DIRECTORIES))
		return exclude ? path_excluded : path_untracked;

	untracked = lookup_untracked(dir->untracked, untracked,
				     dirname + baselen, len - baselen);

	/*
	 * If this is an excluded directory, then we only need to check if
	 * the directory contains any files.
	 */
	return read_directory_recursive(dir, istate, dirname, len,
					untracked, 1, exclude, pathspec);
}