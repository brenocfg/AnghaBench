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
struct mlx5e_priv {int num_tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_close_tis (struct mlx5e_priv*,int) ; 

__attribute__((used)) static void
mlx5e_close_tises(struct mlx5e_priv *priv)
{
	int num_tc = priv->num_tc;
	int tc;

	for (tc = 0; tc < num_tc; tc++)
		mlx5e_close_tis(priv, tc);
}