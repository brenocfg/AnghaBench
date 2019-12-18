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
struct drm_mode_destroy_dumb {int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* dumb_destroy ) (struct drm_file*,struct drm_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (struct drm_file*,struct drm_device*,int /*<<< orphan*/ ) ; 

int drm_mode_destroy_dumb_ioctl(struct drm_device *dev,
				void *data, struct drm_file *file_priv)
{
	struct drm_mode_destroy_dumb *args = data;

	if (!dev->driver->dumb_destroy)
		return -ENOSYS;

	return dev->driver->dumb_destroy(file_priv, dev, args->handle);
}