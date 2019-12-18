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
typedef  int u64 ;
struct page {int dummy; } ;
struct mthca_user_db_table {int /*<<< orphan*/  mutex; TYPE_2__* page; } ;
struct mthca_uar {int dummy; } ;
struct TYPE_3__ {int uarc_size; } ;
struct mthca_dev {int /*<<< orphan*/  pdev; TYPE_1__ uar_table; } ;
struct TYPE_4__ {int refcount; int uvirt; int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 int MTHCA_DB_REC_PER_PAGE ; 
 int /*<<< orphan*/  MTHCA_ICM_PAGE_SIZE ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int get_user_pages (int,int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 int mthca_MAP_ICM_page (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_uarc_virt (struct mthca_dev*,struct mthca_uar*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pci_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ *) ; 
 struct page* sg_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ,int) ; 

int mthca_map_user_db(struct mthca_dev *dev, struct mthca_uar *uar,
		      struct mthca_user_db_table *db_tab, int index, u64 uaddr)
{
	struct page *pages[1];
	int ret = 0;
	int i;

	if (!mthca_is_memfree(dev))
		return 0;

	if (index < 0 || index > dev->uar_table.uarc_size / 8)
		return -EINVAL;

	mutex_lock(&db_tab->mutex);

	i = index / MTHCA_DB_REC_PER_PAGE;

	if ((db_tab->page[i].refcount >= MTHCA_DB_REC_PER_PAGE)       ||
	    (db_tab->page[i].uvirt && db_tab->page[i].uvirt != uaddr) ||
	    (uaddr & 4095)) {
		ret = -EINVAL;
		goto out;
	}

	if (db_tab->page[i].refcount) {
		++db_tab->page[i].refcount;
		goto out;
	}

	ret = get_user_pages(uaddr & PAGE_MASK, 1, FOLL_WRITE, pages, NULL);
	if (ret < 0)
		goto out;

	sg_set_page(&db_tab->page[i].mem, pages[0], MTHCA_ICM_PAGE_SIZE,
			uaddr & ~PAGE_MASK);

	ret = pci_map_sg(dev->pdev, &db_tab->page[i].mem, 1, PCI_DMA_TODEVICE);
	if (ret < 0) {
		put_page(pages[0]);
		goto out;
	}

	ret = mthca_MAP_ICM_page(dev, sg_dma_address(&db_tab->page[i].mem),
				 mthca_uarc_virt(dev, uar, i));
	if (ret) {
		pci_unmap_sg(dev->pdev, &db_tab->page[i].mem, 1, PCI_DMA_TODEVICE);
		put_page(sg_page(&db_tab->page[i].mem));
		goto out;
	}

	db_tab->page[i].uvirt    = uaddr;
	db_tab->page[i].refcount = 1;

out:
	mutex_unlock(&db_tab->mutex);
	return ret;
}