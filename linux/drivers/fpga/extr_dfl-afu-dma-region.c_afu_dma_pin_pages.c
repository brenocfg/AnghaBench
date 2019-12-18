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
struct page {int dummy; } ;
struct dfl_feature_platform_data {TYPE_1__* dev; } ;
struct dfl_afu_dma_region {int length; int /*<<< orphan*/  pages; int /*<<< orphan*/  user_addr; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mm; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int account_locked_vm (int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int get_user_pages_fast (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_all_pages (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int afu_dma_pin_pages(struct dfl_feature_platform_data *pdata,
			     struct dfl_afu_dma_region *region)
{
	int npages = region->length >> PAGE_SHIFT;
	struct device *dev = &pdata->dev->dev;
	int ret, pinned;

	ret = account_locked_vm(current->mm, npages, true);
	if (ret)
		return ret;

	region->pages = kcalloc(npages, sizeof(struct page *), GFP_KERNEL);
	if (!region->pages) {
		ret = -ENOMEM;
		goto unlock_vm;
	}

	pinned = get_user_pages_fast(region->user_addr, npages, FOLL_WRITE,
				     region->pages);
	if (pinned < 0) {
		ret = pinned;
		goto put_pages;
	} else if (pinned != npages) {
		ret = -EFAULT;
		goto free_pages;
	}

	dev_dbg(dev, "%d pages pinned\n", pinned);

	return 0;

put_pages:
	put_all_pages(region->pages, pinned);
free_pages:
	kfree(region->pages);
unlock_vm:
	account_locked_vm(current->mm, npages, false);
	return ret;
}