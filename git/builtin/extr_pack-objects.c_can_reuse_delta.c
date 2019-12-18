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
struct object_id {int dummy; } ;
struct TYPE_2__ {struct object_id oid; } ;
struct object_entry {TYPE_1__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_git ; 
 scalar_t__ bitmap_has_oid_in_uninteresting (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  in_same_island (struct object_id*,struct object_id*) ; 
 int /*<<< orphan*/  oidread (struct object_id*,unsigned char const*) ; 
 struct object_entry* packlist_find (int /*<<< orphan*/ *,struct object_id*) ; 
 scalar_t__ thin ; 
 int /*<<< orphan*/  to_pack ; 
 scalar_t__ use_delta_islands ; 

__attribute__((used)) static int can_reuse_delta(const unsigned char *base_sha1,
			   struct object_entry *delta,
			   struct object_entry **base_out)
{
	struct object_entry *base;
	struct object_id base_oid;

	if (!base_sha1)
		return 0;

	oidread(&base_oid, base_sha1);

	/*
	 * First see if we're already sending the base (or it's explicitly in
	 * our "excluded" list).
	 */
	base = packlist_find(&to_pack, &base_oid);
	if (base) {
		if (!in_same_island(&delta->idx.oid, &base->idx.oid))
			return 0;
		*base_out = base;
		return 1;
	}

	/*
	 * Otherwise, reachability bitmaps may tell us if the receiver has it,
	 * even if it was buried too deep in history to make it into the
	 * packing list.
	 */
	if (thin && bitmap_has_oid_in_uninteresting(bitmap_git, &base_oid)) {
		if (use_delta_islands) {
			if (!in_same_island(&delta->idx.oid, &base_oid))
				return 0;
		}
		*base_out = NULL;
		return 1;
	}

	return 0;
}