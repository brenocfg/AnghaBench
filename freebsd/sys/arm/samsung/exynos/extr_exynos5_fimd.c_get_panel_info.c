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
struct panel_info {void* backlight_pin; void* clk_div; void* v_front_porch; void* v_pulse_width; void* v_back_porch; void* h_front_porch; void* h_pulse_width; void* h_back_porch; void* height; void* width; } ;
struct fimd_softc {int /*<<< orphan*/  dev; } ;
typedef  int phandle_t ;
typedef  void* pcell_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  OF_getencprop (int,char*,void**,int) ; 
 int OF_getproplen (int,char*) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_panel_info(struct fimd_softc *sc, struct panel_info *panel)
{
	phandle_t node;
	pcell_t dts_value[3];
	int len;

	if ((node = ofw_bus_get_node(sc->dev)) == -1)
		return (ENXIO);

	/* panel size */
	if ((len = OF_getproplen(node, "panel-size")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "panel-size", dts_value, len);
	panel->width = dts_value[0];
	panel->height = dts_value[1];

	/* hsync */
	if ((len = OF_getproplen(node, "panel-hsync")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "panel-hsync", dts_value, len);
	panel->h_back_porch = dts_value[0];
	panel->h_pulse_width = dts_value[1];
	panel->h_front_porch = dts_value[2];

	/* vsync */
	if ((len = OF_getproplen(node, "panel-vsync")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "panel-vsync", dts_value, len);
	panel->v_back_porch = dts_value[0];
	panel->v_pulse_width = dts_value[1];
	panel->v_front_porch = dts_value[2];

	/* clk divider */
	if ((len = OF_getproplen(node, "panel-clk-div")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "panel-clk-div", dts_value, len);
	panel->clk_div = dts_value[0];

	/* backlight pin */
	if ((len = OF_getproplen(node, "panel-backlight-pin")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "panel-backlight-pin", dts_value, len);
	panel->backlight_pin = dts_value[0];

	return (0);
}