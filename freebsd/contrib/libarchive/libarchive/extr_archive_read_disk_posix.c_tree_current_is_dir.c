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
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int hasLstat ; 
 struct stat* tree_current_lstat (struct tree*) ; 
 struct stat* tree_current_stat (struct tree*) ; 

__attribute__((used)) static int
tree_current_is_dir(struct tree *t)
{
	const struct stat *st;
	/*
	 * If we already have lstat() info, then try some
	 * cheap tests to determine if this is a dir.
	 */
	if (t->flags & hasLstat) {
		/* If lstat() says it's a dir, it must be a dir. */
		st = tree_current_lstat(t);
		if (st == NULL)
			return 0;
		if (S_ISDIR(st->st_mode))
			return 1;
		/* Not a dir; might be a link to a dir. */
		/* If it's not a link, then it's not a link to a dir. */
		if (!S_ISLNK(st->st_mode))
			return 0;
		/*
		 * It's a link, but we don't know what it's a link to,
		 * so we'll have to use stat().
		 */
	}

	st = tree_current_stat(t);
	/* If we can't stat it, it's not a dir. */
	if (st == NULL)
		return 0;
	/* Use the definitive test.  Hopefully this is cached. */
	return (S_ISDIR(st->st_mode));
}