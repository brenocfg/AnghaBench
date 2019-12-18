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
struct mtree_writer {struct mtree_entry* mtree_entry; } ;
struct mtree_entry {scalar_t__ reg_info; } ;
struct archive_write {struct mtree_writer* format_data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  sum_final (struct mtree_writer*,scalar_t__) ; 

__attribute__((used)) static int
archive_write_mtree_finish_entry(struct archive_write *a)
{
	struct mtree_writer *mtree = a->format_data;
	struct mtree_entry *me;

	if ((me = mtree->mtree_entry) == NULL)
		return (ARCHIVE_OK);
	mtree->mtree_entry = NULL;

	if (me->reg_info)
		sum_final(mtree, me->reg_info);

	return (ARCHIVE_OK);
}