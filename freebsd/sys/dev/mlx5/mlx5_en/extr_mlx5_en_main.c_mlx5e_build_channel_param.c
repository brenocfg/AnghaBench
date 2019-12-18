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
struct mlx5e_priv {int dummy; } ;
struct mlx5e_channel_param {int /*<<< orphan*/  tx_cq; int /*<<< orphan*/  rx_cq; int /*<<< orphan*/  sq; int /*<<< orphan*/  rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mlx5e_channel_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5e_build_rq_param (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_rx_cq_param (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_sq_param (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_tx_cq_param (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_build_channel_param(struct mlx5e_priv *priv,
    struct mlx5e_channel_param *cparam)
{
	memset(cparam, 0, sizeof(*cparam));

	mlx5e_build_rq_param(priv, &cparam->rq);
	mlx5e_build_sq_param(priv, &cparam->sq);
	mlx5e_build_rx_cq_param(priv, &cparam->rx_cq);
	mlx5e_build_tx_cq_param(priv, &cparam->tx_cq);
}