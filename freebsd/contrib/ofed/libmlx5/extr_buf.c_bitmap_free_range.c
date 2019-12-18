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
struct mlx5_bitmap {int max; int top; int mask; int avail; int /*<<< orphan*/  last; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_clear_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bitmap_free_range(struct mlx5_bitmap *bitmap, uint32_t obj,
			      int cnt)
{
	int i;

	obj &= bitmap->max - 1;

	for (i = 0; i < cnt; i++)
		mlx5_clear_bit(obj + i, bitmap->table);
	bitmap->last = min(bitmap->last, obj);
	bitmap->top = (bitmap->top + bitmap->max) & bitmap->mask;
	bitmap->avail += cnt;
}