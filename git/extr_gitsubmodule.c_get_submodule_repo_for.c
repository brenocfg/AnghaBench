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
struct submodule {int /*<<< orphan*/  path; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  free (struct repository*) ; 
 scalar_t__ repo_init (struct repository*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ repo_submodule_init (struct repository*,struct repository*,struct submodule const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_repo_worktree_path (struct strbuf*,struct repository*,char*,int /*<<< orphan*/ ) ; 
 struct repository* xmalloc (int) ; 

__attribute__((used)) static struct repository *get_submodule_repo_for(struct repository *r,
						 const struct submodule *sub)
{
	struct repository *ret = xmalloc(sizeof(*ret));

	if (repo_submodule_init(ret, r, sub)) {
		/*
		 * No entry in .gitmodules? Technically not a submodule,
		 * but historically we supported repositories that happen to be
		 * in-place where a gitlink is. Keep supporting them.
		 */
		struct strbuf gitdir = STRBUF_INIT;
		strbuf_repo_worktree_path(&gitdir, r, "%s/.git", sub->path);
		if (repo_init(ret, gitdir.buf, NULL)) {
			strbuf_release(&gitdir);
			free(ret);
			return NULL;
		}
		strbuf_release(&gitdir);
	}

	return ret;
}