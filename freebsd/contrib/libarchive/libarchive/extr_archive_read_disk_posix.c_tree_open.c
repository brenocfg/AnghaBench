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
struct tree {int initial_symlink_mode; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_string_ensure (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  archive_string_init (int /*<<< orphan*/ *) ; 
 struct tree* calloc (int,int) ; 
 struct tree* tree_reopen (struct tree*,char const*,int) ; 

__attribute__((used)) static struct tree *
tree_open(const char *path, int symlink_mode, int restore_time)
{
	struct tree *t;

	if ((t = calloc(1, sizeof(*t))) == NULL)
		return (NULL);
	archive_string_init(&t->path);
	archive_string_ensure(&t->path, 31);
	t->initial_symlink_mode = symlink_mode;
	return (tree_reopen(t, path, restore_time));
}