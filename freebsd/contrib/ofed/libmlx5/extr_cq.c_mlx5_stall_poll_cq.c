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

/* Variables and functions */
 int /*<<< orphan*/  get_cycles () ; 
 int mlx5_stall_num_loop ; 

__attribute__((used)) static void mlx5_stall_poll_cq(void)
{
	int i;

	for (i = 0; i < mlx5_stall_num_loop; i++)
		(void)get_cycles();
}