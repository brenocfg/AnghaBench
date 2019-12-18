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
typedef  int uint32_t ;
struct ttm_buffer_object {int type; int num_pages; int /*<<< orphan*/  sg; TYPE_2__* ttm; int /*<<< orphan*/  mutex; struct ttm_bo_global* glob; struct ttm_bo_device* bdev; } ;
struct ttm_bo_global {int /*<<< orphan*/  dummy_read_page; } ;
struct ttm_bo_device {TYPE_1__* driver; scalar_t__ need_dma32; } ;
struct TYPE_5__ {int /*<<< orphan*/  sg; } ;
struct TYPE_4__ {TYPE_2__* (* ttm_tt_create ) (struct ttm_bo_device*,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  TTM_ASSERT_LOCKED (int /*<<< orphan*/ *) ; 
 int TTM_PAGE_FLAG_DMA32 ; 
 int TTM_PAGE_FLAG_SG ; 
 int TTM_PAGE_FLAG_ZERO_ALLOC ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_2__* stub1 (struct ttm_bo_device*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* stub2 (struct ttm_bo_device*,int,int,int /*<<< orphan*/ ) ; 
#define  ttm_bo_type_device 130 
#define  ttm_bo_type_kernel 129 
#define  ttm_bo_type_sg 128 
 int /*<<< orphan*/  unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttm_bo_add_ttm(struct ttm_buffer_object *bo, bool zero_alloc)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_bo_global *glob = bo->glob;
	int ret = 0;
	uint32_t page_flags = 0;

	TTM_ASSERT_LOCKED(&bo->mutex);
	bo->ttm = NULL;

	if (bdev->need_dma32)
		page_flags |= TTM_PAGE_FLAG_DMA32;

	switch (bo->type) {
	case ttm_bo_type_device:
		if (zero_alloc)
			page_flags |= TTM_PAGE_FLAG_ZERO_ALLOC;
	case ttm_bo_type_kernel:
		bo->ttm = bdev->driver->ttm_tt_create(bdev, bo->num_pages << PAGE_SHIFT,
						      page_flags, glob->dummy_read_page);
		if (unlikely(bo->ttm == NULL))
			ret = -ENOMEM;
		break;
	case ttm_bo_type_sg:
		bo->ttm = bdev->driver->ttm_tt_create(bdev, bo->num_pages << PAGE_SHIFT,
						      page_flags | TTM_PAGE_FLAG_SG,
						      glob->dummy_read_page);
		if (unlikely(bo->ttm == NULL)) {
			ret = -ENOMEM;
			break;
		}
		bo->ttm->sg = bo->sg;
		break;
	default:
		printf("[TTM] Illegal buffer object type\n");
		ret = -EINVAL;
		break;
	}

	return ret;
}