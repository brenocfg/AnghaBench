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
struct terasic_mtl_softc {int /*<<< orphan*/  mtl_dev; } ;
struct fb_info {int fb_width; int fb_bpp; int fb_depth; int fb_stride; void* fb_height; } ;
typedef  int phandle_t ;
typedef  void* pcell_t ;
typedef  int /*<<< orphan*/  dts_value ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  OF_getencprop (int,char*,void**,int) ; 
 int OF_getproplen (int,char*) ; 
 void* TERASIC_MTL_FB_HEIGHT ; 
 int TERASIC_MTL_FB_WIDTH ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
terasic_mtl_fbd_panel_info(struct terasic_mtl_softc *sc, struct fb_info *info)
{
	phandle_t node;
	pcell_t dts_value[2];
	int len;

	if ((node = ofw_bus_get_node(sc->mtl_dev)) == -1)
		return (ENXIO);

	/* panel size */
	if ((len = OF_getproplen(node, "panel-size")) != sizeof(dts_value))
		return (ENXIO);
	OF_getencprop(node, "panel-size", dts_value, len);
	info->fb_width = dts_value[0];
	info->fb_height = dts_value[1];
	info->fb_bpp = info->fb_depth = 32;
	info->fb_stride = info->fb_width * (info->fb_depth / 8);

	/*
	 * Safety belt to ensure framebuffer params are as expected.  May be
	 * removed when we have full confidence in fdt / hints params.
	 */
	if (info->fb_width != TERASIC_MTL_FB_WIDTH ||
	    info->fb_height != TERASIC_MTL_FB_HEIGHT ||
	    info->fb_stride != 3200 ||
	    info->fb_bpp != 32 || info->fb_depth != 32) {
		device_printf(sc->mtl_dev,
		    "rejecting invalid panel params width=%u height=%u\n",
		    (unsigned)info->fb_width, (unsigned)info->fb_height);
		return (EINVAL);
	}

	return (0);
}