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
typedef  int u32 ;
struct mlx4_bitmap {int max; int reserved_top; } ;

/* Variables and functions */

__attribute__((used)) static u32 mlx4_bitmap_masked_value(struct mlx4_bitmap *bitmap, u32 obj)
{
	return obj & (bitmap->max + bitmap->reserved_top - 1);
}