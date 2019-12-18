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
struct drm_global_reference {size_t global_type; int /*<<< orphan*/  (* release ) (struct drm_global_reference*) ;int /*<<< orphan*/ * object; } ;
struct drm_global_item {scalar_t__ refcount; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_DRM_GLOBAL ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct drm_global_item* glob ; 
 int /*<<< orphan*/  stub1 (struct drm_global_reference*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

void drm_global_item_unref(struct drm_global_reference *ref)
{
	struct drm_global_item *item = &glob[ref->global_type];

	sx_xlock(&item->mutex);
	MPASS(item->refcount != 0);
	MPASS(ref->object == item->object);
	if (--item->refcount == 0) {
		ref->release(ref);
		free(item->object, M_DRM_GLOBAL);
		item->object = NULL;
	}
	sx_xunlock(&item->mutex);
}