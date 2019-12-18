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
struct submodule {int /*<<< orphan*/  path; int /*<<< orphan*/  name; } ;
struct strbuf {int /*<<< orphan*/ * buf; } ;
struct repository {char* submodule_prefix; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ repo_init (struct repository*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_repo_git_path (struct strbuf*,struct repository*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_repo_worktree_path (struct strbuf*,struct repository*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 char* xstrfmt (char*,char*,int /*<<< orphan*/ ) ; 

int repo_submodule_init(struct repository *subrepo,
			struct repository *superproject,
			const struct submodule *sub)
{
	struct strbuf gitdir = STRBUF_INIT;
	struct strbuf worktree = STRBUF_INIT;
	int ret = 0;

	if (!sub) {
		ret = -1;
		goto out;
	}

	strbuf_repo_worktree_path(&gitdir, superproject, "%s/.git", sub->path);
	strbuf_repo_worktree_path(&worktree, superproject, "%s", sub->path);

	if (repo_init(subrepo, gitdir.buf, worktree.buf)) {
		/*
		 * If initilization fails then it may be due to the submodule
		 * not being populated in the superproject's worktree.  Instead
		 * we can try to initilize the submodule by finding it's gitdir
		 * in the superproject's 'modules' directory.  In this case the
		 * submodule would not have a worktree.
		 */
		strbuf_reset(&gitdir);
		strbuf_repo_git_path(&gitdir, superproject,
				     "modules/%s", sub->name);

		if (repo_init(subrepo, gitdir.buf, NULL)) {
			ret = -1;
			goto out;
		}
	}

	subrepo->submodule_prefix = xstrfmt("%s%s/",
					    superproject->submodule_prefix ?
					    superproject->submodule_prefix :
					    "", sub->path);

out:
	strbuf_release(&gitdir);
	strbuf_release(&worktree);
	return ret;
}