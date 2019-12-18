#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;
union mthca_buf {TYPE_2__* page_list; TYPE_2__ direct; } ;
struct mthca_mr {int dummy; } ;
struct mthca_dev {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  mthca_free_mr (struct mthca_dev*,struct mthca_mr*) ; 

void mthca_buf_free(struct mthca_dev *dev, int size, union mthca_buf *buf,
		    int is_direct, struct mthca_mr *mr)
{
	int i;

	if (mr)
		mthca_free_mr(dev, mr);

	if (is_direct)
		dma_free_coherent(&dev->pdev->dev, size, buf->direct.buf,
				  dma_unmap_addr(&buf->direct, mapping));
	else {
		for (i = 0; i < (size + PAGE_SIZE - 1) / PAGE_SIZE; ++i)
			dma_free_coherent(&dev->pdev->dev, PAGE_SIZE,
					  buf->page_list[i].buf,
					  dma_unmap_addr(&buf->page_list[i],
							 mapping));
		kfree(buf->page_list);
	}
}