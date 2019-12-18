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
typedef  int uint32_t ;
struct mlx5_bitmap {int max; int last; int top; int mask; int avail; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int find_aligned_range (int /*<<< orphan*/ ,int,int,int,int) ; 
 int mlx5_bitmap_alloc (struct mlx5_bitmap*) ; 
 int /*<<< orphan*/  mlx5_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bitmap_alloc_range(struct mlx5_bitmap *bitmap, int cnt,
			      int align)
{
	uint32_t obj;
	int ret, i;

	if (cnt == 1 && align == 1)
		return mlx5_bitmap_alloc(bitmap);

	if (cnt > bitmap->max)
		return -1;

	obj = find_aligned_range(bitmap->table, bitmap->last,
				 bitmap->max, cnt, align);
	if (obj >= bitmap->max) {
		bitmap->top = (bitmap->top + bitmap->max) & bitmap->mask;
		obj = find_aligned_range(bitmap->table, 0, bitmap->max,
					 cnt, align);
	}

	if (obj < bitmap->max) {
		for (i = 0; i < cnt; i++)
			mlx5_set_bit(obj + i, bitmap->table);
		if (obj == bitmap->last) {
			bitmap->last = (obj + cnt);
			if (bitmap->last >= bitmap->max)
				bitmap->last = 0;
		}
		obj |= bitmap->top;
		ret = obj;
	} else
		ret = -1;

	if (ret != -1)
		bitmap->avail -= cnt;

	return obj;
}