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
struct vt_device {struct vga_softc* vd_softc; } ;
struct vga_softc {int vga_wmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_WRITE1 (struct vga_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VGA_GC_ADDRESS ; 
 int /*<<< orphan*/  VGA_GC_DATA ; 
 int VGA_GC_MODE ; 
 int /*<<< orphan*/  VGA_SEQ_ADDRESS ; 
 int /*<<< orphan*/  VGA_SEQ_DATA ; 
 int VGA_SEQ_MAP_MASK ; 
 int VGA_SEQ_MM_EM0 ; 
 int VGA_SEQ_MM_EM1 ; 
 int VGA_SEQ_MM_EM2 ; 
 int VGA_SEQ_MM_EM3 ; 

__attribute__((used)) static inline void
vga_setwmode(struct vt_device *vd, int wmode)
{
	struct vga_softc *sc = vd->vd_softc;

	if (sc->vga_wmode == wmode)
		return;

	REG_WRITE1(sc, VGA_GC_ADDRESS, VGA_GC_MODE);
	REG_WRITE1(sc, VGA_GC_DATA, wmode);
	sc->vga_wmode = wmode;

	switch (wmode) {
	case 3:
		/* Re-enable all plans. */
		REG_WRITE1(sc, VGA_SEQ_ADDRESS, VGA_SEQ_MAP_MASK);
		REG_WRITE1(sc, VGA_SEQ_DATA, VGA_SEQ_MM_EM3 | VGA_SEQ_MM_EM2 |
		    VGA_SEQ_MM_EM1 | VGA_SEQ_MM_EM0);
		break;
	}
}