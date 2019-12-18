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
struct tree {int flags; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int hasStat ; 
 struct stat* tree_current_lstat (struct tree*) ; 
 struct stat* tree_current_stat (struct tree*) ; 

__attribute__((used)) static int
tree_current_is_physical_dir(struct tree *t)
{
	const struct stat *st;

	/*
	 * If stat() says it isn't a dir, then it's not a dir.
	 * If stat() data is cached, this check is free, so do it first.
	 */
	if (t->flags & hasStat) {
		st = tree_current_stat(t);
		if (st == NULL)
			return (0);
		if (!S_ISDIR(st->st_mode))
			return (0);
	}

	/*
	 * Either stat() said it was a dir (in which case, we have
	 * to determine whether it's really a link to a dir) or
	 * stat() info wasn't available.  So we use lstat(), which
	 * hopefully is already cached.
	 */

	st = tree_current_lstat(t);
	/* If we can't stat it, it's not a dir. */
	if (st == NULL)
		return 0;
	/* Use the definitive test.  Hopefully this is cached. */
	return (S_ISDIR(st->st_mode));
}