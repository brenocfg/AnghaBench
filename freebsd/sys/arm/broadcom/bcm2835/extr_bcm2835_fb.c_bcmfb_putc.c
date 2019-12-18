#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
struct TYPE_5__ {int vi_width; int vi_cheight; int vi_cwidth; } ;
struct TYPE_6__ {TYPE_1__ va_info; } ;
typedef  TYPE_2__ video_adapter_t ;
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int u_char ;
struct bcmsc_softc {scalar_t__ fb_addr; int* font; int ymargin; int stride; int depth; int xmargin; int /*<<< orphan*/  fbswap; } ;
struct TYPE_7__ {int b; int g; int r; int a; } ;

/* Variables and functions */
 int BCMFB_FONT_HEIGHT ; 
 TYPE_4__* bcmfb_palette ; 

__attribute__((used)) static int
bcmfb_putc(video_adapter_t *adp, vm_offset_t off, uint8_t c, uint8_t a)
{
	int bytes, col, i, j, k, row;
	struct bcmsc_softc *sc;
	u_char *p;
	uint8_t *addr, fg, bg, color;
	uint16_t rgb;

	sc = (struct bcmsc_softc *)adp;

	if (sc->fb_addr == 0)
		return (0);

	row = (off / adp->va_info.vi_width) * adp->va_info.vi_cheight;
	col = (off % adp->va_info.vi_width) * adp->va_info.vi_cwidth;
	p = sc->font + c*BCMFB_FONT_HEIGHT;
	addr = (uint8_t *)sc->fb_addr
	    + (row + sc->ymargin)*(sc->stride)
	    + (sc->depth/8) * (col + sc->xmargin);

	fg = a & 0xf ;
	bg = (a >> 4) & 0xf;

	bytes = sc->depth / 8;
	for (i = 0; i < BCMFB_FONT_HEIGHT; i++) {
		for (j = 0, k = 7; j < 8; j++, k--) {
			if ((p[i] & (1 << k)) == 0)
				color = bg;
			else
				color = fg;

			switch (sc->depth) {
			case 32:
			case 24:
				if (sc->fbswap) {
					addr[bytes * j + 0] =
					    bcmfb_palette[color].b;
					addr[bytes * j + 1] =
					    bcmfb_palette[color].g;
					addr[bytes * j + 2] =
					    bcmfb_palette[color].r;
				} else {
					addr[bytes * j + 0] =
					    bcmfb_palette[color].r;
					addr[bytes * j + 1] =
					    bcmfb_palette[color].g;
					addr[bytes * j + 2] =
					    bcmfb_palette[color].b;
				}
				if (sc->depth == 32)
					addr[bytes * j + 3] =
					    bcmfb_palette[color].a;
				break;
			case 16:
				rgb = (bcmfb_palette[color].r >> 3) << 11;
				rgb |= (bcmfb_palette[color].g >> 2) << 5;
				rgb |= (bcmfb_palette[color].b >> 3);
				addr[bytes * j] = rgb & 0xff;
				addr[bytes * j + 1] = (rgb >> 8) & 0xff;
			default:
				/* Not supported yet */
				break;
			}
		}

		addr += (sc->stride);
	}

        return (0);
}