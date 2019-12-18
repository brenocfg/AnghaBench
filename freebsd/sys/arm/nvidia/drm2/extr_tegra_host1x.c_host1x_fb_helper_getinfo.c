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
struct host1x_softc {TYPE_1__* tegra_drm; } ;
struct fb_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  drm_dev; } ;

/* Variables and functions */
 struct host1x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct fb_info* tegra_drm_fb_getinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fb_info *
host1x_fb_helper_getinfo(device_t dev)
{
	struct host1x_softc *sc;

	sc = device_get_softc(dev);
	if (sc->tegra_drm == NULL)
		return (NULL);
	return (tegra_drm_fb_getinfo(&sc->tegra_drm->drm_dev));
}