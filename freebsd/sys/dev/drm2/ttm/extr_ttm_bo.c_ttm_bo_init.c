#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vm_object {int dummy; } ;
struct ttm_placement {int dummy; } ;
struct ttm_mem_global {int dummy; } ;
struct TYPE_4__ {int io_reserved_vm; scalar_t__ io_reserved_count; } ;
struct TYPE_5__ {unsigned long size; unsigned long num_pages; int placement; TYPE_1__ bus; int /*<<< orphan*/  page_alignment; int /*<<< orphan*/ * mm_node; int /*<<< orphan*/  mem_type; } ;
struct ttm_buffer_object {void (* destroy ) (struct ttm_buffer_object*) ;int type; unsigned long num_pages; int seq_valid; size_t acc_size; TYPE_3__* glob; struct sg_table* sg; struct vm_object* persistent_swap_storage; TYPE_2__ mem; scalar_t__ priv_flags; struct ttm_bo_device* bdev; int /*<<< orphan*/  io_reserve_lru; int /*<<< orphan*/  swap; int /*<<< orphan*/  ddestroy; int /*<<< orphan*/  lru; int /*<<< orphan*/  reserved; int /*<<< orphan*/  cpu_writers; int /*<<< orphan*/  list_kref; int /*<<< orphan*/  kref; } ;
struct ttm_bo_device {TYPE_3__* glob; } ;
struct sg_table {int dummy; } ;
typedef  enum ttm_bo_type { ____Placeholder_ttm_bo_type } ttm_bo_type ;
struct TYPE_6__ {int /*<<< orphan*/  bo_count; struct ttm_mem_global* mem_glob; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_TTM_BO ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int TTM_PL_FLAG_CACHED ; 
 int TTM_PL_FLAG_SYSTEM ; 
 int /*<<< orphan*/  TTM_PL_SYSTEM ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct ttm_buffer_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 void stub1 (struct ttm_buffer_object*) ; 
 void stub2 (struct ttm_buffer_object*) ; 
 int ttm_bo_check_placement (struct ttm_buffer_object*,struct ttm_placement*) ; 
 int ttm_bo_setup_vm (struct ttm_buffer_object*) ; 
 scalar_t__ ttm_bo_type_device ; 
 scalar_t__ ttm_bo_type_sg ; 
 int /*<<< orphan*/  ttm_bo_unref (struct ttm_buffer_object**) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 
 int ttm_bo_validate (struct ttm_buffer_object*,struct ttm_placement*,int,int) ; 
 int ttm_mem_global_alloc (struct ttm_mem_global*,size_t,int,int) ; 
 int /*<<< orphan*/  ttm_mem_global_free (struct ttm_mem_global*,size_t) ; 
 scalar_t__ unlikely (int) ; 

int ttm_bo_init(struct ttm_bo_device *bdev,
		struct ttm_buffer_object *bo,
		unsigned long size,
		enum ttm_bo_type type,
		struct ttm_placement *placement,
		uint32_t page_alignment,
		bool interruptible,
		struct vm_object *persistent_swap_storage,
		size_t acc_size,
		struct sg_table *sg,
		void (*destroy) (struct ttm_buffer_object *))
{
	int ret = 0;
	unsigned long num_pages;
	struct ttm_mem_global *mem_glob = bdev->glob->mem_glob;

	ret = ttm_mem_global_alloc(mem_glob, acc_size, false, false);
	if (ret) {
		printf("[TTM] Out of kernel memory\n");
		if (destroy)
			(*destroy)(bo);
		else
			free(bo, M_TTM_BO);
		return -ENOMEM;
	}

	num_pages = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	if (num_pages == 0) {
		printf("[TTM] Illegal buffer object size\n");
		if (destroy)
			(*destroy)(bo);
		else
			free(bo, M_TTM_BO);
		ttm_mem_global_free(mem_glob, acc_size);
		return -EINVAL;
	}
	bo->destroy = destroy;

	refcount_init(&bo->kref, 1);
	refcount_init(&bo->list_kref, 1);
	atomic_set(&bo->cpu_writers, 0);
	atomic_set(&bo->reserved, 1);
	INIT_LIST_HEAD(&bo->lru);
	INIT_LIST_HEAD(&bo->ddestroy);
	INIT_LIST_HEAD(&bo->swap);
	INIT_LIST_HEAD(&bo->io_reserve_lru);
	bo->bdev = bdev;
	bo->glob = bdev->glob;
	bo->type = type;
	bo->num_pages = num_pages;
	bo->mem.size = num_pages << PAGE_SHIFT;
	bo->mem.mem_type = TTM_PL_SYSTEM;
	bo->mem.num_pages = bo->num_pages;
	bo->mem.mm_node = NULL;
	bo->mem.page_alignment = page_alignment;
	bo->mem.bus.io_reserved_vm = false;
	bo->mem.bus.io_reserved_count = 0;
	bo->priv_flags = 0;
	bo->mem.placement = (TTM_PL_FLAG_SYSTEM | TTM_PL_FLAG_CACHED);
	bo->seq_valid = false;
	bo->persistent_swap_storage = persistent_swap_storage;
	bo->acc_size = acc_size;
	bo->sg = sg;
	atomic_inc(&bo->glob->bo_count);

	ret = ttm_bo_check_placement(bo, placement);
	if (unlikely(ret != 0))
		goto out_err;

	/*
	 * For ttm_bo_type_device buffers, allocate
	 * address space from the device.
	 */
	if (bo->type == ttm_bo_type_device ||
	    bo->type == ttm_bo_type_sg) {
		ret = ttm_bo_setup_vm(bo);
		if (ret)
			goto out_err;
	}

	ret = ttm_bo_validate(bo, placement, interruptible, false);
	if (ret)
		goto out_err;

	ttm_bo_unreserve(bo);
	return 0;

out_err:
	ttm_bo_unreserve(bo);
	ttm_bo_unref(&bo);

	return ret;
}