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
struct mlx5e_sq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_destroy_sq (struct mlx5e_sq*) ; 
 int /*<<< orphan*/  mlx5e_disable_sq (struct mlx5e_sq*) ; 
 int /*<<< orphan*/  mlx5e_drain_sq (struct mlx5e_sq*) ; 

__attribute__((used)) static void
mlx5e_close_sq_wait(struct mlx5e_sq *sq)
{

	mlx5e_drain_sq(sq);
	mlx5e_disable_sq(sq);
	mlx5e_destroy_sq(sq);
}