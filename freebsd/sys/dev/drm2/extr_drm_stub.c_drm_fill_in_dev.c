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
struct drm_driver {int driver_features; } ;
struct drm_device {int counters; struct drm_driver* driver; int /*<<< orphan*/ * counts; int /*<<< orphan*/ * types; int /*<<< orphan*/  map_hash; int /*<<< orphan*/  pcir_lock; int /*<<< orphan*/  ctxlist_mutex; int /*<<< orphan*/  dev_struct_lock; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  count_lock; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  vblank_event_list; int /*<<< orphan*/  maplist; int /*<<< orphan*/  ctxlist; int /*<<< orphan*/  filelist; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int DRIVER_GEM ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  _DRM_STAT_CLOSES ; 
 int /*<<< orphan*/  _DRM_STAT_IOCTLS ; 
 int /*<<< orphan*/  _DRM_STAT_LOCK ; 
 int /*<<< orphan*/  _DRM_STAT_LOCKS ; 
 int /*<<< orphan*/  _DRM_STAT_OPENS ; 
 int /*<<< orphan*/  _DRM_STAT_UNLOCKS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_cancel_fill_in_dev (struct drm_device*) ; 
 int drm_ctxbitmap_init (struct drm_device*) ; 
 int drm_gem_init (struct drm_device*) ; 
 scalar_t__ drm_ht_create (int /*<<< orphan*/ *,int) ; 
 int drm_pci_agp_init (struct drm_device*) ; 
 int drm_sysctl_init (struct drm_device*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

int drm_fill_in_dev(struct drm_device *dev,
			   struct drm_driver *driver)
{
	int retcode, i;

	INIT_LIST_HEAD(&dev->filelist);
	INIT_LIST_HEAD(&dev->ctxlist);
	INIT_LIST_HEAD(&dev->maplist);
	INIT_LIST_HEAD(&dev->vblank_event_list);

	mtx_init(&dev->irq_lock, "drmirq", NULL, MTX_DEF);
	mtx_init(&dev->count_lock, "drmcount", NULL, MTX_DEF);
	mtx_init(&dev->event_lock, "drmev", NULL, MTX_DEF);
	sx_init(&dev->dev_struct_lock, "drmslk");
	mtx_init(&dev->ctxlist_mutex, "drmctxlist", NULL, MTX_DEF);
	mtx_init(&dev->pcir_lock, "drmpcir", NULL, MTX_DEF);

	if (drm_ht_create(&dev->map_hash, 12)) {
		return -ENOMEM;
	}

	/* the DRM has 6 basic counters */
	dev->counters = 6;
	dev->types[0] = _DRM_STAT_LOCK;
	dev->types[1] = _DRM_STAT_OPENS;
	dev->types[2] = _DRM_STAT_CLOSES;
	dev->types[3] = _DRM_STAT_IOCTLS;
	dev->types[4] = _DRM_STAT_LOCKS;
	dev->types[5] = _DRM_STAT_UNLOCKS;

	/*
	 * FIXME Linux<->FreeBSD: this is done in drm_setup() on Linux.
	 */
	for (i = 0; i < ARRAY_SIZE(dev->counts); i++)
		atomic_set(&dev->counts[i], 0);

	dev->driver = driver;

	retcode = drm_pci_agp_init(dev);
	if (retcode)
		goto error_out_unreg;



	retcode = drm_ctxbitmap_init(dev);
	if (retcode) {
		DRM_ERROR("Cannot allocate memory for context bitmap.\n");
		goto error_out_unreg;
	}

	if (driver->driver_features & DRIVER_GEM) {
		retcode = drm_gem_init(dev);
		if (retcode) {
			DRM_ERROR("Cannot initialize graphics execution "
				  "manager (GEM)\n");
			goto error_out_unreg;
		}
	}

	retcode = drm_sysctl_init(dev);
	if (retcode != 0) {
		DRM_ERROR("Failed to create hw.dri sysctl entry: %d\n",
		    retcode);
	}

	return 0;

      error_out_unreg:
	drm_cancel_fill_in_dev(dev);
	return retcode;
}