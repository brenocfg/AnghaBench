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
struct mlx5_bitmap {scalar_t__ avail; scalar_t__ max; } ;

/* Variables and functions */

__attribute__((used)) static int bitmap_empty(struct mlx5_bitmap *bitmap)
{
	return (bitmap->avail == bitmap->max) ? 1 : 0;
}