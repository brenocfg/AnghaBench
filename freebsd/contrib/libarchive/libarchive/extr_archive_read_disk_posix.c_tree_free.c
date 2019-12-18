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
struct tree {int max_filesystem_id; struct tree* filesystem_table; struct tree* allocation_ptr; struct tree* sparse_list; struct tree* dirent; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct tree*) ; 

__attribute__((used)) static void
tree_free(struct tree *t)
{
	int i;

	if (t == NULL)
		return;
	archive_string_free(&t->path);
#if defined(USE_READDIR_R)
	free(t->dirent);
#endif
	free(t->sparse_list);
	for (i = 0; i < t->max_filesystem_id; i++)
		free(t->filesystem_table[i].allocation_ptr);
	free(t->filesystem_table);
	free(t);
}