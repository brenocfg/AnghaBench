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
struct mlx5e_rq {int /*<<< orphan*/  rqn; struct mlx5e_channel* channel; } ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5e_channel {struct mlx5e_priv* priv; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_destroy_rq (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlx5e_disable_rq(struct mlx5e_rq *rq)
{
	struct mlx5e_channel *c = rq->channel;
	struct mlx5e_priv *priv = c->priv;
	struct mlx5_core_dev *mdev = priv->mdev;

	mlx5_core_destroy_rq(mdev, rq->rqn);
}