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
typedef  int u_int ;
struct ttm_buffer_object {int /*<<< orphan*/  list_kref; } ;

/* Variables and functions */
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  ttm_bo_release_list (struct ttm_buffer_object*) ; 

void ttm_bo_list_ref_sub(struct ttm_buffer_object *bo, int count,
			 bool never_free)
{
	u_int old;

	old = atomic_fetchadd_int(&bo->list_kref, -count);
	if (old <= count) {
		if (never_free)
			panic("ttm_bo_ref_buf");
		ttm_bo_release_list(bo);
	}
}