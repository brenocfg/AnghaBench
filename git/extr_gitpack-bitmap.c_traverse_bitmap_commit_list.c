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
struct bitmap_index {int /*<<< orphan*/  tags; int /*<<< orphan*/  blobs; int /*<<< orphan*/  trees; int /*<<< orphan*/  commits; int /*<<< orphan*/  result; } ;
typedef  int /*<<< orphan*/  show_reachable_fn ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_BLOB ; 
 int /*<<< orphan*/  OBJ_COMMIT ; 
 int /*<<< orphan*/  OBJ_TAG ; 
 int /*<<< orphan*/  OBJ_TREE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_extended_objects (struct bitmap_index*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_objects_for_type (struct bitmap_index*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void traverse_bitmap_commit_list(struct bitmap_index *bitmap_git,
				 show_reachable_fn show_reachable)
{
	assert(bitmap_git->result);

	show_objects_for_type(bitmap_git, bitmap_git->commits,
		OBJ_COMMIT, show_reachable);
	show_objects_for_type(bitmap_git, bitmap_git->trees,
		OBJ_TREE, show_reachable);
	show_objects_for_type(bitmap_git, bitmap_git->blobs,
		OBJ_BLOB, show_reachable);
	show_objects_for_type(bitmap_git, bitmap_git->tags,
		OBJ_TAG, show_reachable);

	show_extended_objects(bitmap_git, show_reachable);
}