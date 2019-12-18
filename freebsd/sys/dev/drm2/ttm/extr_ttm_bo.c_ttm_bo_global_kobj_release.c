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
struct ttm_bo_global {int /*<<< orphan*/  dummy_read_page; int /*<<< orphan*/  shrink; int /*<<< orphan*/  mem_glob; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_mem_unregister_shrink (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttm_bo_global_kobj_release(struct ttm_bo_global *glob)
{

	ttm_mem_unregister_shrink(glob->mem_glob, &glob->shrink);
	vm_page_free(glob->dummy_read_page);
}