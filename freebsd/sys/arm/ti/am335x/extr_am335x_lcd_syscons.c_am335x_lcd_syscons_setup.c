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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct video_adapter_softc {int depth; int stride; int width; int height; int fb_size; int /*<<< orphan*/  va; int /*<<< orphan*/  fb_paddr; int /*<<< orphan*/  fb_addr; } ;
struct panel_info {int bpp; int panel_width; int panel_height; } ;

/* Variables and functions */
 int /*<<< orphan*/  am335x_syscons_update_margins (int /*<<< orphan*/ *) ; 
 struct video_adapter_softc va_softc ; 

int am335x_lcd_syscons_setup(vm_offset_t vaddr, vm_paddr_t paddr,
    struct panel_info *panel)
{
	struct video_adapter_softc *va_sc = &va_softc;

	va_sc->fb_addr = vaddr;
	va_sc->fb_paddr = paddr;
	va_sc->depth = panel->bpp;
	va_sc->stride = panel->bpp*panel->panel_width/8;

	va_sc->width = panel->panel_width;
	va_sc->height = panel->panel_height;
	va_sc->fb_size = va_sc->width * va_sc->height
	    * va_sc->depth/8;
	am335x_syscons_update_margins(&va_sc->va);

	return (0);
}