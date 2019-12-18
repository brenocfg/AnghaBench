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
struct host1x_softc {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct host1x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int host1x_drm_exit (struct host1x_softc*) ; 
 int /*<<< orphan*/  tegra_drm_fb_destroy (struct drm_device*) ; 

__attribute__((used)) static int
host1x_drm_unload(struct drm_device *drm_dev)
{
	struct host1x_softc *sc;
	int rv;

	sc = device_get_softc(drm_dev->dev);

	drm_kms_helper_poll_fini(drm_dev);
	tegra_drm_fb_destroy(drm_dev);
	drm_mode_config_cleanup(drm_dev);

	rv = host1x_drm_exit(sc);
	if (rv < 0)
		return (rv);
	return (0);
}