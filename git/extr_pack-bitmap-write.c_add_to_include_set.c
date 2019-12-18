#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
struct bitmapped_commit {int /*<<< orphan*/  bitmap; } ;
struct bitmap {int dummy; } ;
typedef  scalar_t__ khiter_t ;
struct TYPE_4__ {int /*<<< orphan*/  bitmaps; } ;

/* Variables and functions */
 scalar_t__ bitmap_get (struct bitmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_or_ewah (struct bitmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (struct bitmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_object_pos (int /*<<< orphan*/ *) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get_oid_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bitmapped_commit* kh_value (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__ writer ; 

__attribute__((used)) static int
add_to_include_set(struct bitmap *base, struct commit *commit)
{
	khiter_t hash_pos;
	uint32_t bitmap_pos = find_object_pos(&commit->object.oid);

	if (bitmap_get(base, bitmap_pos))
		return 0;

	hash_pos = kh_get_oid_map(writer.bitmaps, commit->object.oid);
	if (hash_pos < kh_end(writer.bitmaps)) {
		struct bitmapped_commit *bc = kh_value(writer.bitmaps, hash_pos);
		bitmap_or_ewah(base, bc->bitmap);
		return 0;
	}

	bitmap_set(base, bitmap_pos);
	return 1;
}