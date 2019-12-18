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
struct drm_gem_object {int /*<<< orphan*/  vm_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 

void
drm_gem_object_release(struct drm_gem_object *obj)
{

	/*
	 * obj->vm_obj can be NULL for private gem objects.
	 */
	vm_object_deallocate(obj->vm_obj);
}