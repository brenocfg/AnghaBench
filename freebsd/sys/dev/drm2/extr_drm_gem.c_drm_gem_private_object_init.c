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
struct drm_gem_object {int refcount; size_t size; int /*<<< orphan*/  handle_count; int /*<<< orphan*/ * vm_obj; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int drm_gem_private_object_init(struct drm_device *dev,
			struct drm_gem_object *obj, size_t size)
{
	MPASS((size & (PAGE_SIZE - 1)) == 0);

	obj->dev = dev;
	obj->vm_obj = NULL;

	obj->refcount = 1;
	atomic_store_rel_int(&obj->handle_count, 0);
	obj->size = size;

	return 0;
}