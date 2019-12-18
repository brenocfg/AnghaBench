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
struct ttm_object_device {int /*<<< orphan*/  object_hash; int /*<<< orphan*/  object_count; int /*<<< orphan*/  object_lock; struct ttm_mem_global* mem_glob; } ;
struct ttm_mem_global {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TTM_OBJ_DEV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_ht_create (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  free (struct ttm_object_device*,int /*<<< orphan*/ ) ; 
 struct ttm_object_device* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 

struct ttm_object_device *ttm_object_device_init(struct ttm_mem_global
						 *mem_glob,
						 unsigned int hash_order)
{
	struct ttm_object_device *tdev;
	int ret;

	tdev = malloc(sizeof(*tdev), M_TTM_OBJ_DEV, M_WAITOK);
	tdev->mem_glob = mem_glob;
	rw_init(&tdev->object_lock, "ttmdo");
	atomic_set(&tdev->object_count, 0);
	ret = drm_ht_create(&tdev->object_hash, hash_order);

	if (ret == 0)
		return tdev;

	free(tdev, M_TTM_OBJ_DEV);
	return NULL;
}