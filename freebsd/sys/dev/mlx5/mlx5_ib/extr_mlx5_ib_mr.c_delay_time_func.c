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
struct mlx5_ib_dev {scalar_t__ fill_delay; } ;

/* Variables and functions */

__attribute__((used)) static void delay_time_func(unsigned long ctx)
{
	struct mlx5_ib_dev *dev = (struct mlx5_ib_dev *)ctx;

	dev->fill_delay = 0;
}