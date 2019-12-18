#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx4_dev {TYPE_3__* persist; } ;
struct TYPE_5__ {scalar_t__ buf; int /*<<< orphan*/  map; } ;
struct mlx4_buf {int nbufs; TYPE_4__* page_list; TYPE_1__ direct; } ;
struct TYPE_8__ {int /*<<< orphan*/  map; scalar_t__ buf; } ;
struct TYPE_7__ {TYPE_2__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 int /*<<< orphan*/  vunmap (scalar_t__) ; 

void mlx4_buf_free(struct mlx4_dev *dev, int size, struct mlx4_buf *buf)
{
	int i;

	if (buf->nbufs == 1)
		dma_free_coherent(&dev->persist->pdev->dev, size,
				  buf->direct.buf,
				  buf->direct.map);
	else {
		if (BITS_PER_LONG == 64)
			vunmap(buf->direct.buf);

		for (i = 0; i < buf->nbufs; ++i)
			if (buf->page_list[i].buf)
				dma_free_coherent(&dev->persist->pdev->dev,
						  PAGE_SIZE,
						  buf->page_list[i].buf,
						  buf->page_list[i].map);
		kfree(buf->page_list);
	}
}