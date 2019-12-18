#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct mlx5_buf {int /*<<< orphan*/  page_list; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  dma_map; TYPE_1__ direct; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void mlx5_buf_free(struct mlx5_core_dev *dev, struct mlx5_buf *buf)
{

	bus_dmamap_unload(buf->dma_tag, buf->dma_map);
	bus_dmamem_free(buf->dma_tag, buf->direct.buf, buf->dma_map);
	bus_dma_tag_destroy(buf->dma_tag);
	kfree(buf->page_list);
}