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
typedef  int /*<<< orphan*/  uint32_t ;
struct vm_object {int dummy; } ;
struct ttm_placement {int dummy; } ;
struct ttm_buffer_object {int dummy; } ;
struct ttm_bo_device {int dummy; } ;
typedef  enum ttm_bo_type { ____Placeholder_ttm_bo_type } ttm_bo_type ;

/* Variables and functions */
 int /*<<< orphan*/  M_TTM_BO ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ likely (int) ; 
 struct ttm_buffer_object* malloc (int,int /*<<< orphan*/ ,int) ; 
 size_t ttm_bo_acc_size (struct ttm_bo_device*,unsigned long,int) ; 
 int ttm_bo_init (struct ttm_bo_device*,struct ttm_buffer_object*,unsigned long,int,struct ttm_placement*,int /*<<< orphan*/ ,int,struct vm_object*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ttm_bo_create(struct ttm_bo_device *bdev,
			unsigned long size,
			enum ttm_bo_type type,
			struct ttm_placement *placement,
			uint32_t page_alignment,
			bool interruptible,
			struct vm_object *persistent_swap_storage,
			struct ttm_buffer_object **p_bo)
{
	struct ttm_buffer_object *bo;
	size_t acc_size;
	int ret;

	bo = malloc(sizeof(*bo), M_TTM_BO, M_WAITOK | M_ZERO);
	acc_size = ttm_bo_acc_size(bdev, size, sizeof(struct ttm_buffer_object));
	ret = ttm_bo_init(bdev, bo, size, type, placement, page_alignment,
			  interruptible, persistent_swap_storage, acc_size,
			  NULL, NULL);
	if (likely(ret == 0))
		*p_bo = bo;

	return ret;
}