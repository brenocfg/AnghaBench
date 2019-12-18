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
typedef  int uint32_t ;
typedef  int u_char ;
struct video_adapter_softc {int bpp; scalar_t__ fb_addr; int* font; int ymargin; int stride; int xmargin; } ;

/* Variables and functions */
 int ENXIO ; 
 int IPU3FB_FONT_HEIGHT ; 
 int* colors ; 
 int* colors_24 ; 

__attribute__((used)) static int
ipu3fb_putc(video_adapter_t *adp, vm_offset_t off, uint8_t c, uint8_t a)
{
	struct video_adapter_softc *sc;
	int col, row, bpp;
	int b, i, j, k;
	uint8_t *addr;
	u_char *p;
	uint32_t fg, bg, color;

	sc = (struct video_adapter_softc *)adp;
	bpp = sc->bpp;

	if (sc->fb_addr == 0)
		return (0);
	row = (off / adp->va_info.vi_width) * adp->va_info.vi_cheight;
	col = (off % adp->va_info.vi_width) * adp->va_info.vi_cwidth;
	p = sc->font + c * IPU3FB_FONT_HEIGHT;
	addr = (uint8_t *)sc->fb_addr
	    + (row + sc->ymargin) * (sc->stride)
	    + bpp * (col + sc->xmargin);

	if (bpp == 2) {
		bg = colors[(a >> 4) & 0x0f];
		fg = colors[a & 0x0f];
	} else if (bpp == 3) {
		bg = colors_24[(a >> 4) & 0x0f];
		fg = colors_24[a & 0x0f];
	} else {
		return (ENXIO);
	}

	for (i = 0; i < IPU3FB_FONT_HEIGHT; i++) {
		for (j = 0, k = 7; j < 8; j++, k--) {
			if ((p[i] & (1 << k)) == 0)
				color = bg;
			else
				color = fg;
			/* FIXME: BPP maybe different */
			for (b = 0; b < bpp; b ++)
				addr[bpp * j + b] =
				    (color >> (b << 3)) & 0xff;
		}

		addr += (sc->stride);
	}

        return (0);
}