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
struct drm_minor {int /*<<< orphan*/  master_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock_queue; int /*<<< orphan*/  spinlock; } ;
struct drm_master {int /*<<< orphan*/  head; struct drm_minor* minor; int /*<<< orphan*/  magicfree; int /*<<< orphan*/  magiclist; TYPE_1__ lock; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INIT_WAITQUEUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_MAGIC_HASH_ORDER ; 
 int /*<<< orphan*/  DRM_MEM_KMS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  drm_ht_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct drm_master* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 

struct drm_master *drm_master_create(struct drm_minor *minor)
{
	struct drm_master *master;

	master = malloc(sizeof(*master), DRM_MEM_KMS, M_NOWAIT | M_ZERO);
	if (!master)
		return NULL;

	refcount_init(&master->refcount, 1);
	mtx_init(&master->lock.spinlock, "drm_master__lock__spinlock",
	    NULL, MTX_DEF);
	DRM_INIT_WAITQUEUE(&master->lock.lock_queue);
	drm_ht_create(&master->magiclist, DRM_MAGIC_HASH_ORDER);
	INIT_LIST_HEAD(&master->magicfree);
	master->minor = minor;

	list_add_tail(&master->head, &minor->master_list);

	return master;
}