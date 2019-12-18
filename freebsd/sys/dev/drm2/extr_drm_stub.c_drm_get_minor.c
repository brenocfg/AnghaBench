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
struct drm_minor {int type; int index; TYPE_1__* device; int /*<<< orphan*/ * buf_sigio; int /*<<< orphan*/  master_list; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct drm_minor* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_DEV_GID ; 
 int /*<<< orphan*/  DRM_DEV_MODE ; 
 int /*<<< orphan*/  DRM_DEV_UID ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_MEM_MINOR ; 
#define  DRM_MINOR_CONTROL 129 
#define  DRM_MINOR_RENDER 128 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAKEDEV_CHECKNAME ; 
 int MAKEDEV_WAITOK ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  drm_cdevsw ; 
 int drm_minor_get_id (struct drm_device*,int) ; 
 int /*<<< orphan*/  free (struct drm_minor*,int /*<<< orphan*/ ) ; 
 int make_dev_p (int,TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 struct drm_minor* malloc (int,int /*<<< orphan*/ ,int) ; 

int drm_get_minor(struct drm_device *dev, struct drm_minor **minor, int type)
{
	struct drm_minor *new_minor;
	int ret;
	int minor_id;
	const char *minor_devname;

	DRM_DEBUG("\n");

	minor_id = drm_minor_get_id(dev, type);
	if (minor_id < 0)
		return minor_id;

	new_minor = malloc(sizeof(struct drm_minor), DRM_MEM_MINOR,
	    M_NOWAIT | M_ZERO);
	if (!new_minor) {
		ret = -ENOMEM;
		goto err_idr;
	}

	new_minor->type = type;
	new_minor->dev = dev;
	new_minor->index = minor_id;
	INIT_LIST_HEAD(&new_minor->master_list);

	new_minor->buf_sigio = NULL;

	switch (type) {
	case DRM_MINOR_CONTROL:
		minor_devname = "dri/controlD%d";
		break;
	case DRM_MINOR_RENDER:
		minor_devname = "dri/renderD%d";
		break;
	default:
		minor_devname = "dri/card%d";
		break;
	}

	ret = make_dev_p(MAKEDEV_WAITOK | MAKEDEV_CHECKNAME, &new_minor->device,
	    &drm_cdevsw, 0, DRM_DEV_UID, DRM_DEV_GID,
	    DRM_DEV_MODE, minor_devname, minor_id);
	if (ret) {
		DRM_ERROR("Failed to create cdev: %d\n", ret);
		goto err_mem;
	}
	new_minor->device->si_drv1 = new_minor;
	*minor = new_minor;

	DRM_DEBUG("new minor assigned %d\n", minor_id);
	return 0;


err_mem:
	free(new_minor, DRM_MEM_MINOR);
err_idr:
	*minor = NULL;
	return ret;
}