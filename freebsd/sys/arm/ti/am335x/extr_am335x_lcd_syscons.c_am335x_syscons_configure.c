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
struct video_adapter_softc {int initialized; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  va; } ;
typedef  int phandle_t ;
typedef  void* pcell_t ;
typedef  int /*<<< orphan*/  cell ;

/* Variables and functions */
 scalar_t__ FB_HEIGHT ; 
 scalar_t__ FB_WIDTH ; 
 int OF_finddevice (char*) ; 
 scalar_t__ OF_getencprop (int,char*,void**,int) ; 
 int am335x_syscons_find_panel_node (int) ; 
 int /*<<< orphan*/  am335x_syscons_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct video_adapter_softc va_softc ; 

__attribute__((used)) static int
am335x_syscons_configure(int flags)
{
	struct video_adapter_softc *va_sc;

	va_sc = &va_softc;
	phandle_t display, root;
	pcell_t cell;

	if (va_sc->initialized)
		return (0);

	va_sc->width = 0;
	va_sc->height = 0;

	/*
	 * It seems there is no way to let syscons framework know
	 * that framebuffer resolution has changed. So just try
	 * to fetch data from FDT and go with defaults if failed
	 */
	root = OF_finddevice("/");
	if ((root != -1) && 
	    (display = am335x_syscons_find_panel_node(root))) {
		if ((OF_getencprop(display, "panel_width", &cell,
		    sizeof(cell))) > 0)
			va_sc->width = cell;

		if ((OF_getencprop(display, "panel_height", &cell,
		    sizeof(cell))) > 0)
			va_sc->height = cell;
	}

	if (va_sc->width == 0)
		va_sc->width = FB_WIDTH;
	if (va_sc->height == 0)
		va_sc->height = FB_HEIGHT;

	am335x_syscons_init(0, &va_sc->va, 0);

	va_sc->initialized = 1;

	return (0);
}