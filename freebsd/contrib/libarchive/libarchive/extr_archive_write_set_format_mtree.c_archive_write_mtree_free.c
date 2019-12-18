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
struct mtree_writer {int /*<<< orphan*/  buf; int /*<<< orphan*/  ebuf; int /*<<< orphan*/  cur_dirstr; } ;
struct archive_write {struct mtree_writer* format_data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  attr_counter_set_free (struct mtree_writer*) ; 
 int /*<<< orphan*/  free (struct mtree_writer*) ; 
 int /*<<< orphan*/  mtree_entry_register_free (struct mtree_writer*) ; 

__attribute__((used)) static int
archive_write_mtree_free(struct archive_write *a)
{
	struct mtree_writer *mtree= a->format_data;

	if (mtree == NULL)
		return (ARCHIVE_OK);

	/* Make sure we do not leave any entries. */
	mtree_entry_register_free(mtree);
	archive_string_free(&mtree->cur_dirstr);
	archive_string_free(&mtree->ebuf);
	archive_string_free(&mtree->buf);
	attr_counter_set_free(mtree);
	free(mtree);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}