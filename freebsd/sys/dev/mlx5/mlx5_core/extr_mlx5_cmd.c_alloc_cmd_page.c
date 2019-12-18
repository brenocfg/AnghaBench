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
struct mlx5_core_dev {TYPE_2__* pdev; } ;
struct mlx5_cmd {int /*<<< orphan*/  dma_sx; int /*<<< orphan*/  dma_mtx; int /*<<< orphan*/  dma_cv; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/ * cmd_page; int /*<<< orphan*/  cmd_buf; int /*<<< orphan*/  dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  bsddev; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_ADAPTER_PAGE_SIZE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * mlx5_fwp_alloc (struct mlx5_core_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_fwp_get_dma (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fwp_get_virt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
alloc_cmd_page(struct mlx5_core_dev *dev, struct mlx5_cmd *cmd)
{
	int err;

	sx_init(&cmd->dma_sx, "MLX5-DMA-SX");
	mtx_init(&cmd->dma_mtx, "MLX5-DMA-MTX", NULL, MTX_DEF);
	cv_init(&cmd->dma_cv, "MLX5-DMA-CV");

	/*
	 * Create global DMA descriptor tag for allocating
	 * 4K firmware pages:
	 */
	err = -bus_dma_tag_create(
	    bus_get_dma_tag(dev->pdev->dev.bsddev),
	    MLX5_ADAPTER_PAGE_SIZE,	/* alignment */
	    0,				/* no boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MLX5_ADAPTER_PAGE_SIZE,	/* maxsize */
	    1,				/* nsegments */
	    MLX5_ADAPTER_PAGE_SIZE,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockfuncarg */
	    &cmd->dma_tag);
	if (err != 0)
		goto failure_destroy_sx;

	cmd->cmd_page = mlx5_fwp_alloc(dev, GFP_KERNEL, 1);
	if (cmd->cmd_page == NULL) {
		err = -ENOMEM;
		goto failure_alloc_page;
	}
	cmd->dma = mlx5_fwp_get_dma(cmd->cmd_page, 0);
	cmd->cmd_buf = mlx5_fwp_get_virt(cmd->cmd_page, 0);
	return (0);

failure_alloc_page:
	bus_dma_tag_destroy(cmd->dma_tag);

failure_destroy_sx:
	cv_destroy(&cmd->dma_cv);
	mtx_destroy(&cmd->dma_mtx);
	sx_destroy(&cmd->dma_sx);
	return (err);
}