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
struct archive_string {int /*<<< orphan*/  s; } ;
struct zip_entry {int /*<<< orphan*/  node; struct archive_string rsrcname; } ;
struct zip {int /*<<< orphan*/  tree; int /*<<< orphan*/  tree_rsrc; } ;

/* Variables and functions */
 scalar_t__ __archive_rb_tree_find_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __archive_rb_tree_insert_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __archive_rb_tree_remove_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 int /*<<< orphan*/  archive_strncpy (struct archive_string*,char const*,size_t) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void
expose_parent_dirs(struct zip *zip, const char *name, size_t name_length)
{
	struct archive_string str;
	struct zip_entry *dir;
	char *s;

	archive_string_init(&str);
	archive_strncpy(&str, name, name_length);
	for (;;) {
		s = strrchr(str.s, '/');
		if (s == NULL)
			break;
		*s = '\0';
		/* Transfer the parent directory from zip->tree_rsrc RB
		 * tree to zip->tree RB tree to expose. */
		dir = (struct zip_entry *)
		    __archive_rb_tree_find_node(&zip->tree_rsrc, str.s);
		if (dir == NULL)
			break;
		__archive_rb_tree_remove_node(&zip->tree_rsrc, &dir->node);
		archive_string_free(&dir->rsrcname);
		__archive_rb_tree_insert_node(&zip->tree, &dir->node);
	}
	archive_string_free(&str);
}