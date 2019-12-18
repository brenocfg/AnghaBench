#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
struct mlx5e_sq {int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  uar; TYPE_2__* priv; int /*<<< orphan*/  wq_ctrl; TYPE_1__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_unmap_free_uar (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_wq_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_free_sq_db (struct mlx5e_sq*) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_destroy_sq(struct mlx5e_sq *sq)
{
	/* destroy all sysctl nodes */
	sysctl_ctx_free(&sq->stats.ctx);

	mlx5e_free_sq_db(sq);
	mlx5_wq_destroy(&sq->wq_ctrl);
	mlx5_unmap_free_uar(sq->priv->mdev, &sq->uar);
	bus_dma_tag_destroy(sq->dma_tag);
}