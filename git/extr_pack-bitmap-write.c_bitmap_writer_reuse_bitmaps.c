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
struct packing_data {int /*<<< orphan*/  repo; } ;
struct bitmap_index {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  show_progress; int /*<<< orphan*/  reused; } ;

/* Variables and functions */
 int /*<<< orphan*/  kh_init_oid_map () ; 
 struct bitmap_index* prepare_bitmap_git (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rebuild_existing_bitmaps (struct bitmap_index*,struct packing_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ writer ; 

void bitmap_writer_reuse_bitmaps(struct packing_data *to_pack)
{
	struct bitmap_index *bitmap_git;
	if (!(bitmap_git = prepare_bitmap_git(to_pack->repo)))
		return;

	writer.reused = kh_init_oid_map();
	rebuild_existing_bitmaps(bitmap_git, to_pack, writer.reused,
				 writer.show_progress);
	/*
	 * NEEDSWORK: rebuild_existing_bitmaps() makes writer.reused reference
	 * some bitmaps in bitmap_git, so we can't free the latter.
	 */
}