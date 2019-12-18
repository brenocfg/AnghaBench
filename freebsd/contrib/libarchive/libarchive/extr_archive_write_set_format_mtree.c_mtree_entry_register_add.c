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
struct TYPE_2__ {struct mtree_entry** last; } ;
struct mtree_writer {TYPE_1__ file_list; } ;
struct mtree_entry {struct mtree_entry* next; } ;

/* Variables and functions */

__attribute__((used)) static void
mtree_entry_register_add(struct mtree_writer *mtree, struct mtree_entry *file)
{
        file->next = NULL;
        *mtree->file_list.last = file;
        mtree->file_list.last = &(file->next);
}