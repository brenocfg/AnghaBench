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
struct video_adapter_softc {scalar_t__ fb_addr; int* font; int ymargin; int stride; int depth; int xmargin; } ;
struct TYPE_7__ {int r; int g; int b; int a; } ;

/* Variables and functions */
 int AM335X_FONT_HEIGHT ; 
 TYPE_4__* am335x_syscons_palette ; 

__attribute__((used)) static int
am335x_syscons_putc(video_adapter_t *adp, vm_offset_t off, uint8_t c, uint8_t a)
{
	struct video_adapter_softc *sc;
	int row;
	int col;
	int i, j, k;
	uint8_t *addr;
	u_char *p;
	uint8_t fg, bg, color;
	uint16_t rgb;

	sc = (struct video_adapter_softc *)adp;

	if (sc->fb_addr == 0)
		return (0);

	row = (off / adp->va_info.vi_width) * adp->va_info.vi_cheight;
	col = (off % adp->va_info.vi_width) * adp->va_info.vi_cwidth;
	p = sc->font + c*AM335X_FONT_HEIGHT;
	addr = (uint8_t *)sc->fb_addr
	    + (row + sc->ymargin)*(sc->stride)
	    + (sc->depth/8) * (col + sc->xmargin);

	fg = a & 0xf ;
	bg = (a >> 4) & 0xf;

	for (i = 0; i < AM335X_FONT_HEIGHT; i++) {
		for (j = 0, k = 7; j < 8; j++, k--) {
			if ((p[i] & (1 << k)) == 0)
				color = bg;
			else
				color = fg;

			switch (sc->depth) {
			case 32:
				addr[4*j+0] = am335x_syscons_palette[color].r;
				addr[4*j+1] = am335x_syscons_palette[color].g;
				addr[4*j+2] = am335x_syscons_palette[color].b;
				addr[4*j+3] = am335x_syscons_palette[color].a;
				break;
			case 24:
				addr[3*j] = am335x_syscons_palette[color].r;
				addr[3*j+1] = am335x_syscons_palette[color].g;
				addr[3*j+2] = am335x_syscons_palette[color].b;
				break;
			case 16:
				rgb = (am335x_syscons_palette[color].r >> 3) << 11;
				rgb |= (am335x_syscons_palette[color].g >> 2) << 5;
				rgb |= (am335x_syscons_palette[color].b >> 3);
				addr[2*j] = rgb & 0xff;
				addr[2*j + 1] = (rgb >> 8) & 0xff;
			default:
				/* Not supported yet */
				break;
			}
		}

		addr += (sc->stride);
	}

        return (0);
}