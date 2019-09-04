#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* current; } ;
typedef  TYPE_2__ tree_iterator_frame ;
struct TYPE_12__ {TYPE_5__* tree_entry; } ;
typedef  TYPE_3__ tree_iterator_entry ;
struct TYPE_15__ {int /*<<< orphan*/  id; int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_13__ {TYPE_9__ entry; TYPE_1__ entry_path; } ;
typedef  TYPE_4__ tree_iterator ;
struct TYPE_14__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  attr; } ;
typedef  TYPE_5__ git_tree_entry ;
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int,int) ; 

__attribute__((used)) static void tree_iterator_set_current(
	tree_iterator *iter,
	tree_iterator_frame *frame,
	tree_iterator_entry *entry)
{
	git_tree_entry *tree_entry = entry->tree_entry;

	frame->current = entry;

	memset(&iter->entry, 0x0, sizeof(git_index_entry));

	iter->entry.mode = tree_entry->attr;
	iter->entry.path = iter->entry_path.ptr;
	git_oid_cpy(&iter->entry.id, tree_entry->oid);
}