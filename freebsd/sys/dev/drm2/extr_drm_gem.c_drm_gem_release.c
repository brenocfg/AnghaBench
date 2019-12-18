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
struct drm_file {int /*<<< orphan*/  object_names; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_names_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_names_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct drm_file*) ; 
 int /*<<< orphan*/  drm_gem_object_release_handle ; 

void
drm_gem_release(struct drm_device *dev, struct drm_file *file_private)
{
	drm_gem_names_foreach(&file_private->object_names,
	    drm_gem_object_release_handle, file_private);

	drm_gem_names_fini(&file_private->object_names);
}