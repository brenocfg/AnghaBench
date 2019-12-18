#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
struct TYPE_4__ {int vi_width; int vi_cheight; int vi_cwidth; } ;
struct TYPE_5__ {TYPE_1__ va_info; } ;
typedef  TYPE_2__ video_adapter_t ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_char ;
struct ofwfb_softc {int* sc_font; int sc_font_height; int sc_ymargin; int sc_stride; int sc_xmargin; scalar_t__ sc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ofwfb_background (int) ; 
 int /*<<< orphan*/  ofwfb_foreground (int) ; 
 int /*<<< orphan*/  ofwfb_pix32 (struct ofwfb_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofwfb_putc32(video_adapter_t *adp, vm_offset_t off, uint8_t c, uint8_t a)
{
	struct ofwfb_softc *sc;
	int row;
	int col;
	int i, j, k;
	uint32_t *addr, fg, bg;
	u_char *p;

	sc = (struct ofwfb_softc *)adp;
        row = (off / adp->va_info.vi_width) * adp->va_info.vi_cheight;
        col = (off % adp->va_info.vi_width) * adp->va_info.vi_cwidth;
	p = sc->sc_font + c*sc->sc_font_height;
	addr = (uint32_t *)sc->sc_addr
		+ (row + sc->sc_ymargin)*(sc->sc_stride/4)
		+ col + sc->sc_xmargin;

	fg = ofwfb_pix32(sc, ofwfb_foreground(a));
	bg = ofwfb_pix32(sc, ofwfb_background(a));

	for (i = 0; i < sc->sc_font_height; i++) {
		for (j = 0, k = 7; j < 8; j++, k--) {
			if ((p[i] & (1 << k)) == 0)
				*(addr + j) = bg;
			else
				*(addr + j) = fg;
		}
		addr += (sc->sc_stride/4);
	}

	return (0);
}