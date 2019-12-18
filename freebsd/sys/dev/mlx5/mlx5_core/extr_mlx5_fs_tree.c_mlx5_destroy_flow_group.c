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
struct mlx5_flow_group {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  fs_remove_node (int /*<<< orphan*/ *) ; 

void mlx5_destroy_flow_group(struct mlx5_flow_group *fg)
{
	fs_remove_node(&fg->base);
}