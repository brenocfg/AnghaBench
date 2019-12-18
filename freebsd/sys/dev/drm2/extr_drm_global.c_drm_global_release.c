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
struct drm_global_item {scalar_t__ refcount; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int DRM_GLOBAL_NUM ; 
 int /*<<< orphan*/  MPASS (int) ; 
 struct drm_global_item* glob ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

void drm_global_release(void)
{
	int i;
	for (i = 0; i < DRM_GLOBAL_NUM; ++i) {
		struct drm_global_item *item = &glob[i];
		MPASS(item->object == NULL);
		MPASS(item->refcount == 0);
		sx_destroy(&item->mutex);
	}
}