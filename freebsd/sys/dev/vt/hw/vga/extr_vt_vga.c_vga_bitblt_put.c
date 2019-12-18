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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  term_color_t ;
struct vt_device {struct vga_softc* vd_softc; } ;
struct vga_softc {int vga_curbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_READ1 (struct vga_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_WRITE1 (struct vga_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_setfg (struct vt_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vga_bitblt_put(struct vt_device *vd, u_long dst, term_color_t color,
    uint8_t v)
{
	struct vga_softc *sc = vd->vd_softc;

	/* Skip empty writes, in order to avoid palette changes. */
	if (v != 0x00) {
		vga_setfg(vd, color);
		/*
		 * When this MEM_READ1() gets disabled, all sorts of
		 * artifacts occur.  This is because this read loads the
		 * set of 8 pixels that are about to be changed.  There
		 * is one scenario where we can avoid the read, namely
		 * if all pixels are about to be overwritten anyway.
		 */
		if (v != 0xff) {
			MEM_READ1(sc, dst);

			/* The bg color was trashed by the reads. */
			sc->vga_curbg = 0xff;
		}
		MEM_WRITE1(sc, dst, v);
	}
}