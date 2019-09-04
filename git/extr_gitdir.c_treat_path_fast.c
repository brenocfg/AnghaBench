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
struct untracked_cache_dir {int dummy; } ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct pathspec {int dummy; } ;
struct index_state {int dummy; } ;
struct dir_struct {int dummy; } ;
struct cached_dir {TYPE_1__* ucd; int /*<<< orphan*/  file; } ;
typedef  enum path_treatment { ____Placeholder_path_treatment } path_treatment ;
struct TYPE_2__ {scalar_t__ check_only; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int path_recurse ; 
 int path_untracked ; 
 int read_directory_recursive (struct dir_struct*,struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,struct pathspec const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_complete (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 

__attribute__((used)) static enum path_treatment treat_path_fast(struct dir_struct *dir,
					   struct untracked_cache_dir *untracked,
					   struct cached_dir *cdir,
					   struct index_state *istate,
					   struct strbuf *path,
					   int baselen,
					   const struct pathspec *pathspec)
{
	strbuf_setlen(path, baselen);
	if (!cdir->ucd) {
		strbuf_addstr(path, cdir->file);
		return path_untracked;
	}
	strbuf_addstr(path, cdir->ucd->name);
	/* treat_one_path() does this before it calls treat_directory() */
	strbuf_complete(path, '/');
	if (cdir->ucd->check_only)
		/*
		 * check_only is set as a result of treat_directory() getting
		 * to its bottom. Verify again the same set of directories
		 * with check_only set.
		 */
		return read_directory_recursive(dir, istate, path->buf, path->len,
						cdir->ucd, 1, 0, pathspec);
	/*
	 * We get path_recurse in the first run when
	 * directory_exists_in_index() returns index_nonexistent. We
	 * are sure that new changes in the index does not impact the
	 * outcome. Return now.
	 */
	return path_recurse;
}