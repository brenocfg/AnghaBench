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
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int drm_gem_handle_delete (struct drm_file*,unsigned int) ; 

__attribute__((used)) static int
tegra_bo_dumb_destroy(struct drm_file *file_priv, struct drm_device *drm_dev,
    unsigned int handle)
{
	int rv;

	rv = drm_gem_handle_delete(file_priv, handle);
	return (rv);
}