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
typedef  int uintmax_t ;
struct ttm_mem_type_manager {int has_type; int use_type; int flags; int gpu_offset; int available_caching; int default_caching; TYPE_1__* func; scalar_t__ size; } ;
struct ttm_bo_device {struct ttm_mem_type_manager* man; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* debug ) (struct ttm_mem_type_manager*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PFX ; 
 int TTM_PL_SYSTEM ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stub1 (struct ttm_mem_type_manager*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttm_mem_type_debug(struct ttm_bo_device *bdev, int mem_type)
{
	struct ttm_mem_type_manager *man = &bdev->man[mem_type];

	printf("    has_type: %d\n", man->has_type);
	printf("    use_type: %d\n", man->use_type);
	printf("    flags: 0x%08X\n", man->flags);
	printf("    gpu_offset: 0x%08lX\n", man->gpu_offset);
	printf("    size: %ju\n", (uintmax_t)man->size);
	printf("    available_caching: 0x%08X\n", man->available_caching);
	printf("    default_caching: 0x%08X\n", man->default_caching);
	if (mem_type != TTM_PL_SYSTEM)
		(*man->func->debug)(man, TTM_PFX);
}