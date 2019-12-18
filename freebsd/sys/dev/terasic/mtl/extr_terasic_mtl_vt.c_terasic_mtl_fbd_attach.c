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
struct fb_info {intptr_t fb_vbase; int fb_bpp; int fb_depth; int fb_width; int fb_height; int fb_stride; int /*<<< orphan*/  fb_size; int /*<<< orphan*/  fb_pbase; int /*<<< orphan*/  fb_name; } ;
struct terasic_mtl_softc {int /*<<< orphan*/  mtl_dev; int /*<<< orphan*/  mtl_pixel_res; struct fb_info mtl_fb_info; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ *) ; 
 scalar_t__ pmap_mapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 
 scalar_t__ terasic_mtl_fbd_panel_info (struct terasic_mtl_softc*,struct fb_info*) ; 

int
terasic_mtl_fbd_attach(struct terasic_mtl_softc *sc)
{
	struct fb_info *info;
	device_t fbd;

	info = &sc->mtl_fb_info;
	info->fb_name = device_get_nameunit(sc->mtl_dev);
	info->fb_pbase = rman_get_start(sc->mtl_pixel_res);
	info->fb_size = rman_get_size(sc->mtl_pixel_res);
	info->fb_vbase = (intptr_t)pmap_mapdev(info->fb_pbase, info->fb_size);
	if (terasic_mtl_fbd_panel_info(sc, info) != 0) {
		device_printf(sc->mtl_dev, "using default panel params\n");
		info->fb_bpp = info->fb_depth = 32;
		info->fb_width = 800;
		info->fb_height = 480;
		info->fb_stride = info->fb_width * (info->fb_depth / 8);
	}

	fbd = device_add_child(sc->mtl_dev, "fbd",
	    device_get_unit(sc->mtl_dev));
	if (fbd == NULL) {
		device_printf(sc->mtl_dev, "Failed to attach fbd child\n");
		return (ENXIO);
	}
	if (device_probe_and_attach(fbd) != 0) {
		device_printf(sc->mtl_dev,
		    "Failed to attach fbd device\n");
		return (ENXIO);
	}
	return (0);
}