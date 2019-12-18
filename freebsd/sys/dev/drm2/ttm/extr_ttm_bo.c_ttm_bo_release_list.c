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
struct TYPE_4__ {int /*<<< orphan*/ * mm_node; } ;
struct ttm_buffer_object {size_t acc_size; int /*<<< orphan*/  (* destroy ) (struct ttm_buffer_object*) ;TYPE_2__* glob; scalar_t__ ttm; int /*<<< orphan*/  ddestroy; int /*<<< orphan*/  lru; TYPE_1__ mem; int /*<<< orphan*/ * sync_obj; int /*<<< orphan*/  cpu_writers; int /*<<< orphan*/  kref; int /*<<< orphan*/  list_kref; struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {TYPE_3__* glob; } ;
struct TYPE_6__ {int /*<<< orphan*/  mem_glob; } ;
struct TYPE_5__ {int /*<<< orphan*/  bo_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_TTM_BO ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ttm_buffer_object*,int /*<<< orphan*/ ) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_mem_global_free (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ttm_tt_destroy (scalar_t__) ; 

__attribute__((used)) static void ttm_bo_release_list(struct ttm_buffer_object *bo)
{
	struct ttm_bo_device *bdev = bo->bdev;
	size_t acc_size = bo->acc_size;

	MPASS(atomic_read(&bo->list_kref) == 0);
	MPASS(atomic_read(&bo->kref) == 0);
	MPASS(atomic_read(&bo->cpu_writers) == 0);
	MPASS(bo->sync_obj == NULL);
	MPASS(bo->mem.mm_node == NULL);
	MPASS(list_empty(&bo->lru));
	MPASS(list_empty(&bo->ddestroy));

	if (bo->ttm)
		ttm_tt_destroy(bo->ttm);
	atomic_dec(&bo->glob->bo_count);
	if (bo->destroy)
		bo->destroy(bo);
	else {
		free(bo, M_TTM_BO);
	}
	ttm_mem_global_free(bdev->glob->mem_glob, acc_size);
}