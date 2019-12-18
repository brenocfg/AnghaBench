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
typedef  int /*<<< orphan*/  uint64_t ;
struct ttm_bo_global {int /*<<< orphan*/  device_list_mutex; int /*<<< orphan*/  device_list; } ;
struct ttm_bo_driver {int dummy; } ;
struct ttm_bo_device {int need_dma32; int /*<<< orphan*/  device_list; int /*<<< orphan*/  fence_lock; scalar_t__ val_seq; struct ttm_bo_global* glob; int /*<<< orphan*/ * dev_mapping; int /*<<< orphan*/  ddestroy; int /*<<< orphan*/  wq; int /*<<< orphan*/  addr_space_mm; int /*<<< orphan*/  addr_space_rb; int /*<<< orphan*/  man; struct ttm_bo_driver* driver; int /*<<< orphan*/  vm_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMEOUT_TASK_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ttm_bo_device*) ; 
 int /*<<< orphan*/  TTM_PL_SYSTEM ; 
 int drm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  ttm_bo_clean_mm (struct ttm_bo_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_delayed_workqueue ; 
 int ttm_bo_init_mm (struct ttm_bo_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int ttm_bo_device_init(struct ttm_bo_device *bdev,
		       struct ttm_bo_global *glob,
		       struct ttm_bo_driver *driver,
		       uint64_t file_page_offset,
		       bool need_dma32)
{
	int ret = -EINVAL;

	rw_init(&bdev->vm_lock, "ttmvml");
	bdev->driver = driver;

	memset(bdev->man, 0, sizeof(bdev->man));

	/*
	 * Initialize the system memory buffer type.
	 * Other types need to be driver / IOCTL initialized.
	 */
	ret = ttm_bo_init_mm(bdev, TTM_PL_SYSTEM, 0);
	if (unlikely(ret != 0))
		goto out_no_sys;

	RB_INIT(&bdev->addr_space_rb);
	ret = drm_mm_init(&bdev->addr_space_mm, file_page_offset, 0x10000000);
	if (unlikely(ret != 0))
		goto out_no_addr_mm;

	TIMEOUT_TASK_INIT(taskqueue_thread, &bdev->wq, 0,
	    ttm_bo_delayed_workqueue, bdev);
	INIT_LIST_HEAD(&bdev->ddestroy);
	bdev->dev_mapping = NULL;
	bdev->glob = glob;
	bdev->need_dma32 = need_dma32;
	bdev->val_seq = 0;
	mtx_init(&bdev->fence_lock, "ttmfence", NULL, MTX_DEF);
	sx_xlock(&glob->device_list_mutex);
	list_add_tail(&bdev->device_list, &glob->device_list);
	sx_xunlock(&glob->device_list_mutex);

	return 0;
out_no_addr_mm:
	ttm_bo_clean_mm(bdev, 0);
out_no_sys:
	return ret;
}