#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_type_manager {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; scalar_t__ offset; scalar_t__ base; void* addr; int /*<<< orphan*/  is_iomem; } ;
struct ttm_mem_reg {size_t mem_type; int placement; TYPE_1__ bus; } ;
struct ttm_bo_device {struct ttm_mem_type_manager* man; } ;

/* Variables and functions */
 int ENOMEM ; 
 int TTM_PL_FLAG_WC ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 void* pmap_mapdev_attr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_mem_io_free (struct ttm_bo_device*,struct ttm_mem_reg*) ; 
 int /*<<< orphan*/  ttm_mem_io_lock (struct ttm_mem_type_manager*,int) ; 
 int ttm_mem_io_reserve (struct ttm_bo_device*,struct ttm_mem_reg*) ; 
 int /*<<< orphan*/  ttm_mem_io_unlock (struct ttm_mem_type_manager*) ; 

__attribute__((used)) static
int ttm_mem_reg_ioremap(struct ttm_bo_device *bdev, struct ttm_mem_reg *mem,
			void **virtual)
{
	struct ttm_mem_type_manager *man = &bdev->man[mem->mem_type];
	int ret;
	void *addr;

	*virtual = NULL;
	(void) ttm_mem_io_lock(man, false);
	ret = ttm_mem_io_reserve(bdev, mem);
	ttm_mem_io_unlock(man);
	if (ret || !mem->bus.is_iomem)
		return ret;

	if (mem->bus.addr) {
		addr = mem->bus.addr;
	} else {
		addr = pmap_mapdev_attr(mem->bus.base + mem->bus.offset,
		    mem->bus.size, (mem->placement & TTM_PL_FLAG_WC) ?
		    VM_MEMATTR_WRITE_COMBINING : VM_MEMATTR_UNCACHEABLE);
		if (!addr) {
			(void) ttm_mem_io_lock(man, false);
			ttm_mem_io_free(bdev, mem);
			ttm_mem_io_unlock(man);
			return -ENOMEM;
		}
	}
	*virtual = addr;
	return 0;
}