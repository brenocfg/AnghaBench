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
struct stat {int dummy; } ;
struct tree {int flags; struct stat const st; } ;

/* Variables and functions */
 scalar_t__ fstatat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stat const*,int /*<<< orphan*/ ) ; 
 int hasStat ; 
 scalar_t__ la_stat (int /*<<< orphan*/ ,struct stat const*) ; 
 int /*<<< orphan*/  tree_current_access_path (struct tree*) ; 
 int /*<<< orphan*/  tree_current_dir_fd (struct tree*) ; 
 scalar_t__ tree_enter_working_dir (struct tree*) ; 

__attribute__((used)) static const struct stat *
tree_current_stat(struct tree *t)
{
	if (!(t->flags & hasStat)) {
#ifdef HAVE_FSTATAT
		if (fstatat(tree_current_dir_fd(t),
		    tree_current_access_path(t), &t->st, 0) != 0)
#else
		if (tree_enter_working_dir(t) != 0)
			return NULL;
		if (la_stat(tree_current_access_path(t), &t->st) != 0)
#endif
			return NULL;
		t->flags |= hasStat;
	}
	return (&t->st);
}