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
struct stored_bitmap {int dummy; } ;
struct object_id {int dummy; } ;
struct include_data {scalar_t__ base; scalar_t__ seen; } ;
struct bitmap_index {int /*<<< orphan*/  bitmaps; } ;
typedef  scalar_t__ khiter_t ;

/* Variables and functions */
 scalar_t__ bitmap_get (scalar_t__,int) ; 
 int /*<<< orphan*/  bitmap_or_ewah (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (scalar_t__,int) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get_oid_map (int /*<<< orphan*/ ,struct object_id const) ; 
 struct stored_bitmap* kh_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lookup_stored_bitmap (struct stored_bitmap*) ; 

__attribute__((used)) static int add_to_include_set(struct bitmap_index *bitmap_git,
			      struct include_data *data,
			      const struct object_id *oid,
			      int bitmap_pos)
{
	khiter_t hash_pos;

	if (data->seen && bitmap_get(data->seen, bitmap_pos))
		return 0;

	if (bitmap_get(data->base, bitmap_pos))
		return 0;

	hash_pos = kh_get_oid_map(bitmap_git->bitmaps, *oid);
	if (hash_pos < kh_end(bitmap_git->bitmaps)) {
		struct stored_bitmap *st = kh_value(bitmap_git->bitmaps, hash_pos);
		bitmap_or_ewah(data->base, lookup_stored_bitmap(st));
		return 0;
	}

	bitmap_set(data->base, bitmap_pos);
	return 1;
}