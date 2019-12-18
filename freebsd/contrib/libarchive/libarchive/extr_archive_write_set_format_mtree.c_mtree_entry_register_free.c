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
struct TYPE_2__ {struct mtree_entry* first; } ;
struct mtree_writer {TYPE_1__ file_list; } ;
struct mtree_entry {struct mtree_entry* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtree_entry_free (struct mtree_entry*) ; 

__attribute__((used)) static void
mtree_entry_register_free(struct mtree_writer *mtree)
{
	struct mtree_entry *file, *file_next;

	file = mtree->file_list.first;
	while (file != NULL) {
		file_next = file->next;
		mtree_entry_free(file);
		file = file_next;
	}
}