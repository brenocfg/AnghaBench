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
struct TYPE_2__ {int /*<<< orphan*/ * first; int /*<<< orphan*/ ** last; } ;
struct mtree_writer {TYPE_1__ file_list; } ;

/* Variables and functions */

__attribute__((used)) static void
mtree_entry_register_init(struct mtree_writer *mtree)
{
	mtree->file_list.first = NULL;
	mtree->file_list.last = &(mtree->file_list.first);
}