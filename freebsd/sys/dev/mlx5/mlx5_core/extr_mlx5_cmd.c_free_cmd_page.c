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
struct mlx5_core_dev {int dummy; } ;
struct mlx5_cmd {int /*<<< orphan*/  dma_sx; int /*<<< orphan*/  dma_mtx; int /*<<< orphan*/  dma_cv; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  cmd_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fwp_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_cmd_page(struct mlx5_core_dev *dev, struct mlx5_cmd *cmd)
{

	mlx5_fwp_free(cmd->cmd_page);
	bus_dma_tag_destroy(cmd->dma_tag);
	cv_destroy(&cmd->dma_cv);
	mtx_destroy(&cmd->dma_mtx);
	sx_destroy(&cmd->dma_sx);
}