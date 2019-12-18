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
struct iso9660 {int /*<<< orphan*/  hardlink_rbtree; } ;
struct archive_rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_RB_DIR_RIGHT ; 
 struct archive_rb_node* ARCHIVE_RB_TREE_MIN (int /*<<< orphan*/ *) ; 
 struct archive_rb_node* __archive_rb_tree_iterate (int /*<<< orphan*/ *,struct archive_rb_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct archive_rb_node*) ; 

__attribute__((used)) static void
isofile_free_hardlinks(struct iso9660 *iso9660)
{
	struct archive_rb_node *n, *next;

	for (n = ARCHIVE_RB_TREE_MIN(&(iso9660->hardlink_rbtree)); n;) {
		next = __archive_rb_tree_iterate(&(iso9660->hardlink_rbtree),
		    n, ARCHIVE_RB_DIR_RIGHT);
		free(n);
		n = next;
	}
}