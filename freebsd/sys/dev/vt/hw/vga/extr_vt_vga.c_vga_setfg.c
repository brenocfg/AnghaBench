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
typedef  size_t term_color_t ;
struct vt_device {struct vga_softc* vd_softc; } ;
struct vga_softc {size_t vga_curfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_WRITE1 (struct vga_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGA_GC_ADDRESS ; 
 int /*<<< orphan*/  VGA_GC_DATA ; 
 int /*<<< orphan*/  VGA_GC_SET_RESET ; 
 int /*<<< orphan*/ * cons_to_vga_colors ; 
 int /*<<< orphan*/  vga_setwmode (struct vt_device*,int) ; 

__attribute__((used)) static inline void
vga_setfg(struct vt_device *vd, term_color_t color)
{
	struct vga_softc *sc = vd->vd_softc;

	vga_setwmode(vd, 3);

	if (sc->vga_curfg == color)
		return;

	REG_WRITE1(sc, VGA_GC_ADDRESS, VGA_GC_SET_RESET);
	REG_WRITE1(sc, VGA_GC_DATA, cons_to_vga_colors[color]);
	sc->vga_curfg = color;
}