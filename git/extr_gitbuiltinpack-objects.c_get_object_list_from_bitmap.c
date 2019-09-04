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
struct rev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_object_entry_from_bitmap ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  bitmap_git ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_result ; 
 scalar_t__ pack_options_allow_reuse () ; 
 int /*<<< orphan*/  prepare_bitmap_walk (struct rev_info*) ; 
 int /*<<< orphan*/  progress_state ; 
 int /*<<< orphan*/  reuse_packfile ; 
 scalar_t__ reuse_packfile_objects ; 
 int /*<<< orphan*/  reuse_packfile_offset ; 
 int /*<<< orphan*/  reuse_partial_packfile_from_bitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  traverse_bitmap_commit_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_object_list_from_bitmap(struct rev_info *revs)
{
	if (!(bitmap_git = prepare_bitmap_walk(revs)))
		return -1;

	if (pack_options_allow_reuse() &&
	    !reuse_partial_packfile_from_bitmap(
			bitmap_git,
			&reuse_packfile,
			&reuse_packfile_objects,
			&reuse_packfile_offset)) {
		assert(reuse_packfile_objects);
		nr_result += reuse_packfile_objects;
		display_progress(progress_state, nr_result);
	}

	traverse_bitmap_commit_list(bitmap_git, &add_object_entry_from_bitmap);
	return 0;
}