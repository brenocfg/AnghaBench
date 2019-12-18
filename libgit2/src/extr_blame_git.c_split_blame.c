#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ suspect; } ;
typedef  TYPE_1__ git_blame__entry ;
typedef  int /*<<< orphan*/  git_blame ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  add_blame_entry (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dup_entry (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* git__malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static int split_blame(git_blame *blame, git_blame__entry *split, git_blame__entry *e)
{
	git_blame__entry *new_entry;

	if (split[0].suspect && split[2].suspect) {
		/* The first part (reuse storage for the existing entry e */
		dup_entry(e, &split[0]);

		/* The last part -- me */
		new_entry = git__malloc(sizeof(*new_entry));
		GIT_ERROR_CHECK_ALLOC(new_entry);
		memcpy(new_entry, &(split[2]), sizeof(git_blame__entry));
		add_blame_entry(blame, new_entry);

		/* ... and the middle part -- parent */
		new_entry = git__malloc(sizeof(*new_entry));
		GIT_ERROR_CHECK_ALLOC(new_entry);
		memcpy(new_entry, &(split[1]), sizeof(git_blame__entry));
		add_blame_entry(blame, new_entry);
	} else if (!split[0].suspect && !split[2].suspect) {
		/*
		 * The parent covers the entire area; reuse storage for e and replace it
		 * with the parent
		 */
		dup_entry(e, &split[1]);
	} else if (split[0].suspect) {
		/* me and then parent */
		dup_entry(e, &split[0]);
		new_entry = git__malloc(sizeof(*new_entry));
		GIT_ERROR_CHECK_ALLOC(new_entry);
		memcpy(new_entry, &(split[1]), sizeof(git_blame__entry));
		add_blame_entry(blame, new_entry);
	} else {
		/* parent and then me */
		dup_entry(e, &split[1]);
		new_entry = git__malloc(sizeof(*new_entry));
		GIT_ERROR_CHECK_ALLOC(new_entry);
		memcpy(new_entry, &(split[2]), sizeof(git_blame__entry));
		add_blame_entry(blame, new_entry);
	}

	return 0;
}