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
struct object_id {int dummy; } ;
struct island_bitmap {int dummy; } ;
typedef  scalar_t__ khiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  island_bitmap_is_subset (struct island_bitmap*,struct island_bitmap*) ; 
 int /*<<< orphan*/  island_marks ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get_oid_map (int /*<<< orphan*/ ,struct object_id const) ; 
 struct island_bitmap* kh_value (int /*<<< orphan*/ ,scalar_t__) ; 

int island_delta_cmp(const struct object_id *a, const struct object_id *b)
{
	khiter_t a_pos, b_pos;
	struct island_bitmap *a_bitmap = NULL, *b_bitmap = NULL;

	if (!island_marks)
		return 0;

	a_pos = kh_get_oid_map(island_marks, *a);
	if (a_pos < kh_end(island_marks))
		a_bitmap = kh_value(island_marks, a_pos);

	b_pos = kh_get_oid_map(island_marks, *b);
	if (b_pos < kh_end(island_marks))
		b_bitmap = kh_value(island_marks, b_pos);

	if (a_bitmap) {
		if (!b_bitmap || !island_bitmap_is_subset(a_bitmap, b_bitmap))
			return -1;
	}
	if (b_bitmap) {
		if (!a_bitmap || !island_bitmap_is_subset(b_bitmap, a_bitmap))
			return 1;
	}

	return 0;
}