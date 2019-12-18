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
struct ttm_range_manager {int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;
struct ttm_mem_type_manager {struct ttm_range_manager* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_TTM_RMAN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int drm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  free (struct ttm_range_manager*,int /*<<< orphan*/ ) ; 
 struct ttm_range_manager* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttm_bo_man_init(struct ttm_mem_type_manager *man,
			   unsigned long p_size)
{
	struct ttm_range_manager *rman;
	int ret;

	rman = malloc(sizeof(*rman), M_TTM_RMAN, M_ZERO | M_WAITOK);
	ret = drm_mm_init(&rman->mm, 0, p_size);
	if (ret) {
		free(rman, M_TTM_RMAN);
		return ret;
	}

	mtx_init(&rman->lock, "ttmrman", NULL, MTX_DEF);
	man->priv = rman;
	return 0;
}