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
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_ADDED ; 
 int /*<<< orphan*/  OBJ_COMMIT ; 
 int /*<<< orphan*/  add_object_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_commit_for_bitmap (struct commit*) ; 
 int /*<<< orphan*/  propagate_island_marks (struct commit*) ; 
 scalar_t__ use_delta_islands ; 
 scalar_t__ write_bitmap_index ; 

__attribute__((used)) static void show_commit(struct commit *commit, void *data)
{
	add_object_entry(&commit->object.oid, OBJ_COMMIT, NULL, 0);
	commit->object.flags |= OBJECT_ADDED;

	if (write_bitmap_index)
		index_commit_for_bitmap(commit);

	if (use_delta_islands)
		propagate_island_marks(commit);
}