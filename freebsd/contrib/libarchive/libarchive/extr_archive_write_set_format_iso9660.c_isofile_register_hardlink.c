#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct isofile {int /*<<< orphan*/  entry; struct isofile* hlnext; } ;
struct iso9660 {int /*<<< orphan*/  hardlink_rbtree; } ;
struct TYPE_2__ {struct isofile** last; struct isofile* first; } ;
struct hardlink {int nlink; TYPE_1__ file_list; } ;
struct archive_write {int /*<<< orphan*/  archive; struct iso9660* format_data; } ;
struct archive_rb_node {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ __archive_rb_tree_find_node (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  __archive_rb_tree_insert_node (int /*<<< orphan*/ *,struct archive_rb_node*) ; 
 char* archive_entry_hardlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_nlink (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  archive_entry_unset_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct hardlink* malloc (int) ; 

__attribute__((used)) static int
isofile_register_hardlink(struct archive_write *a, struct isofile *file)
{
	struct iso9660 *iso9660 = a->format_data;
	struct hardlink *hl;
	const char *pathname;

	archive_entry_set_nlink(file->entry, 1);
	pathname = archive_entry_hardlink(file->entry);
	if (pathname == NULL) {
		/* This `file` is a hardlink target. */
		hl = malloc(sizeof(*hl));
		if (hl == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory");
			return (ARCHIVE_FATAL);
		}
		hl->nlink = 1;
		/* A hardlink target must be the first position. */
		file->hlnext = NULL;
		hl->file_list.first = file;
		hl->file_list.last = &(file->hlnext);
		__archive_rb_tree_insert_node(&(iso9660->hardlink_rbtree),
		    (struct archive_rb_node *)hl);
	} else {
		hl = (struct hardlink *)__archive_rb_tree_find_node(
		    &(iso9660->hardlink_rbtree), pathname);
		if (hl != NULL) {
			/* Insert `file` entry into the tail. */
			file->hlnext = NULL;
			*hl->file_list.last = file;
			hl->file_list.last = &(file->hlnext);
			hl->nlink++;
		}
		archive_entry_unset_size(file->entry);
	}

	return (ARCHIVE_OK);
}