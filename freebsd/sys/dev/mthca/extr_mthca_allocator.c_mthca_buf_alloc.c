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
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;
union mthca_buf {TYPE_2__* page_list; TYPE_2__ direct; } ;
typedef  int u64 ;
struct mthca_pd {int /*<<< orphan*/  pd_num; } ;
struct mthca_mr {int dummy; } ;
struct mthca_dev {TYPE_1__* pdev; } ;
typedef  int dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MTHCA_MPT_FLAG_LOCAL_READ ; 
 int MTHCA_MPT_FLAG_LOCAL_WRITE ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  clear_page (int /*<<< orphan*/ *) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int get_order (int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mthca_buf_free (struct mthca_dev*,int,union mthca_buf*,int,int /*<<< orphan*/ *) ; 
 int mthca_mr_alloc_phys (struct mthca_dev*,int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ ,int,int,struct mthca_mr*) ; 

int mthca_buf_alloc(struct mthca_dev *dev, int size, int max_direct,
		    union mthca_buf *buf, int *is_direct, struct mthca_pd *pd,
		    int hca_write, struct mthca_mr *mr)
{
	int err = -ENOMEM;
	int npages, shift;
	u64 *dma_list = NULL;
	dma_addr_t t;
	int i;

	if (size <= max_direct) {
		*is_direct = 1;
		npages     = 1;
		shift      = get_order(size) + PAGE_SHIFT;

		buf->direct.buf = dma_alloc_coherent(&dev->pdev->dev,
						     size, &t, GFP_KERNEL);
		if (!buf->direct.buf)
			return -ENOMEM;

		dma_unmap_addr_set(&buf->direct, mapping, t);

		memset(buf->direct.buf, 0, size);

		while (t & ((1 << shift) - 1)) {
			--shift;
			npages *= 2;
		}

		dma_list = kmalloc(npages * sizeof *dma_list, GFP_KERNEL);
		if (!dma_list)
			goto err_free;

		for (i = 0; i < npages; ++i)
			dma_list[i] = t + i * (1 << shift);
	} else {
		*is_direct = 0;
		npages     = (size + PAGE_SIZE - 1) / PAGE_SIZE;
		shift      = PAGE_SHIFT;

		dma_list = kmalloc(npages * sizeof *dma_list, GFP_KERNEL);
		if (!dma_list)
			return -ENOMEM;

		buf->page_list = kmalloc(npages * sizeof *buf->page_list,
					 GFP_KERNEL);
		if (!buf->page_list)
			goto err_out;

		for (i = 0; i < npages; ++i)
			buf->page_list[i].buf = NULL;

		for (i = 0; i < npages; ++i) {
			buf->page_list[i].buf =
				dma_alloc_coherent(&dev->pdev->dev, PAGE_SIZE,
						   &t, GFP_KERNEL);
			if (!buf->page_list[i].buf)
				goto err_free;

			dma_list[i] = t;
			dma_unmap_addr_set(&buf->page_list[i], mapping, t);

			clear_page(buf->page_list[i].buf);
		}
	}

	err = mthca_mr_alloc_phys(dev, pd->pd_num,
				  dma_list, shift, npages,
				  0, size,
				  MTHCA_MPT_FLAG_LOCAL_READ |
				  (hca_write ? MTHCA_MPT_FLAG_LOCAL_WRITE : 0),
				  mr);
	if (err)
		goto err_free;

	kfree(dma_list);

	return 0;

err_free:
	mthca_buf_free(dev, size, buf, *is_direct, NULL);

err_out:
	kfree(dma_list);

	return err;
}