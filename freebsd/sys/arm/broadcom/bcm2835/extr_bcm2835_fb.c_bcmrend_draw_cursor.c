#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int vi_width; int vi_height; int vi_cheight; int vi_cwidth; } ;
struct TYPE_10__ {TYPE_3__ va_info; } ;
typedef  TYPE_4__ video_adapter_t ;
typedef  int uint8_t ;
struct bcmsc_softc {scalar_t__ fb_addr; int ymargin; int stride; int depth; int xmargin; } ;
struct TYPE_8__ {scalar_t__ height; } ;
struct TYPE_11__ {TYPE_2__ curs_attr; TYPE_1__* sc; } ;
typedef  TYPE_5__ scr_stat ;
struct TYPE_7__ {TYPE_4__* adp; } ;

/* Variables and functions */

__attribute__((used)) static void
bcmrend_draw_cursor(scr_stat* scp, int off, int blink, int on, int flip)
{
	int bytes, col, i, j, row;
	struct bcmsc_softc *sc;
	uint8_t *addr;
	video_adapter_t *adp;

	adp = scp->sc->adp;
	sc = (struct bcmsc_softc *)adp;

	if (scp->curs_attr.height <= 0)
		return;

	if (sc->fb_addr == 0)
		return;

	if (off >= adp->va_info.vi_width * adp->va_info.vi_height)
		return;

	/* calculate the coordinates in the video buffer */
	row = (off / adp->va_info.vi_width) * adp->va_info.vi_cheight;
	col = (off % adp->va_info.vi_width) * adp->va_info.vi_cwidth;

	addr = (uint8_t *)sc->fb_addr
	    + (row + sc->ymargin)*(sc->stride)
	    + (sc->depth/8) * (col + sc->xmargin);

	bytes = sc->depth / 8;
	/* our cursor consists of simply inverting the char under it */
	for (i = 0; i < adp->va_info.vi_cheight; i++) {
		for (j = 0; j < adp->va_info.vi_cwidth; j++) {
			switch (sc->depth) {
			case 32:
			case 24:
				addr[bytes*j + 2] ^= 0xff;
				/* FALLTHROUGH */
			case 16:
				addr[bytes*j + 1] ^= 0xff;
				addr[bytes*j] ^= 0xff;
				break;
			default:
				break;
			}
		}

		addr += sc->stride;
	}
}