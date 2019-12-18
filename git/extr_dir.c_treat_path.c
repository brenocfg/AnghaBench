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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct pathspec {int dummy; } ;
struct index_state {int dummy; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
struct dir_struct {int dummy; } ;
struct cached_dir {struct dirent* de; } ;
typedef  enum path_treatment { ____Placeholder_path_treatment } path_treatment ;

/* Variables and functions */
 int DTYPE (struct dirent*) ; 
 int /*<<< orphan*/  fspathcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_dot_or_dotdot (int /*<<< orphan*/ ) ; 
 int path_none ; 
 scalar_t__ simplify_away (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pathspec const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int treat_one_path (struct dir_struct*,struct untracked_cache_dir*,struct index_state*,struct strbuf*,int,struct pathspec const*,int,struct dirent*) ; 
 int treat_path_fast (struct dir_struct*,struct untracked_cache_dir*,struct cached_dir*,struct index_state*,struct strbuf*,int,struct pathspec const*) ; 

__attribute__((used)) static enum path_treatment treat_path(struct dir_struct *dir,
				      struct untracked_cache_dir *untracked,
				      struct cached_dir *cdir,
				      struct index_state *istate,
				      struct strbuf *path,
				      int baselen,
				      const struct pathspec *pathspec)
{
	int dtype;
	struct dirent *de = cdir->de;

	if (!de)
		return treat_path_fast(dir, untracked, cdir, istate, path,
				       baselen, pathspec);
	if (is_dot_or_dotdot(de->d_name) || !fspathcmp(de->d_name, ".git"))
		return path_none;
	strbuf_setlen(path, baselen);
	strbuf_addstr(path, de->d_name);
	if (simplify_away(path->buf, path->len, pathspec))
		return path_none;

	dtype = DTYPE(de);
	return treat_one_path(dir, untracked, istate, path, baselen, pathspec, dtype, de);
}