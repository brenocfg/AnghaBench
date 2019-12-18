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
struct worktree {int /*<<< orphan*/  id; int /*<<< orphan*/  is_current; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
#define  REF_TYPE_MAIN_PSEUDOREF 132 
#define  REF_TYPE_NORMAL 131 
#define  REF_TYPE_OTHER_PSEUDOREF 130 
#define  REF_TYPE_PER_WORKTREE 129 
#define  REF_TYPE_PSEUDOREF 128 
 int /*<<< orphan*/  is_main_worktree (struct worktree const*) ; 
 int ref_type (char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 

void strbuf_worktree_ref(const struct worktree *wt,
			 struct strbuf *sb,
			 const char *refname)
{
	switch (ref_type(refname)) {
	case REF_TYPE_PSEUDOREF:
	case REF_TYPE_PER_WORKTREE:
		if (wt && !wt->is_current) {
			if (is_main_worktree(wt))
				strbuf_addstr(sb, "main-worktree/");
			else
				strbuf_addf(sb, "worktrees/%s/", wt->id);
		}
		break;

	case REF_TYPE_MAIN_PSEUDOREF:
	case REF_TYPE_OTHER_PSEUDOREF:
		break;

	case REF_TYPE_NORMAL:
		/*
		 * For shared refs, don't prefix worktrees/ or
		 * main-worktree/. It's not necessary and
		 * files-backend.c can't handle it anyway.
		 */
		break;
	}
	strbuf_addstr(sb, refname);
}