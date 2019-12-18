#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct mlx5_fw_page {int /*<<< orphan*/  dev; int /*<<< orphan*/  load_done; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MLX5_DMA_DONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_DMA_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_DMA_OWNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_DMA_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_LOAD_ST_FAILURE ; 
 int /*<<< orphan*/  MLX5_LOAD_ST_SUCCESS ; 

__attribute__((used)) static void
mlx5_fwp_load_mem_cb(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct mlx5_fw_page *fwp;
	uint8_t owned;

	fwp = (struct mlx5_fw_page *)arg;
	owned = MLX5_DMA_OWNED(fwp->dev);

	if (!owned)
		MLX5_DMA_LOCK(fwp->dev);

	if (error == 0) {
		KASSERT(nseg == 1, ("Number of segments is different from 1"));
		fwp->dma_addr = segs->ds_addr;
		fwp->load_done = MLX5_LOAD_ST_SUCCESS;
	} else {
		fwp->load_done = MLX5_LOAD_ST_FAILURE;
	}
	MLX5_DMA_DONE(fwp->dev);

	if (!owned)
		MLX5_DMA_UNLOCK(fwp->dev);
}