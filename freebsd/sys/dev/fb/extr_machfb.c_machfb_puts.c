#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
struct TYPE_5__ {int vi_width; int vi_cwidth; int vi_cheight; } ;
struct TYPE_6__ {TYPE_1__ va_info; } ;
typedef  TYPE_2__ video_adapter_t ;
typedef  int uint8_t ;
typedef  int uint16_t ;
struct machfb_softc {int sc_xmargin; int sc_ymargin; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACHFB_BLANK ; 
 int /*<<< orphan*/  vidd_putc (TYPE_2__*,int,int,int) ; 

__attribute__((used)) static int
machfb_puts(video_adapter_t *adp, vm_offset_t off, uint16_t *s, int len)
{
	struct machfb_softc *sc;
	int blanks, i, x1, x2, y1, y2;
	uint8_t a, c, color1, color2;

	sc = (struct machfb_softc *)adp;

#define	MACHFB_BLANK	machfb_fill_rect(adp, color1, x1, y1,		\
			    blanks * adp->va_info.vi_cwidth,		\
			    adp->va_info.vi_cheight)

	blanks = color1 = x1 = y1 = 0;
	for (i = 0; i < len; i++) {
		/*
		 * Accelerate continuous blanks by drawing a respective
		 * rectangle instead.  Drawing a rectangle of any size
		 * takes about the same number of operations as drawing
		 * a single character.
		 */
		c = s[i] & 0xff;
		a = (s[i] & 0xff00) >> 8;
		if (c == 0x00 || c == 0x20 || c == 0xdb || c == 0xff) {
			color2 = (a >> (c == 0xdb ? 0 : 4) & 0xf);
			x2 = (((off + i) % adp->va_info.vi_width) *
			    adp->va_info.vi_cwidth) + sc->sc_xmargin;
			y2 = (((off + i) / adp->va_info.vi_width) *
			    adp->va_info.vi_cheight) + sc->sc_ymargin;
			if (blanks == 0) {
				color1 = color2;
				x1 = x2;
				y1 = y2;
				blanks++;
			} else if (color1 != color2 || y1 != y2) {
				MACHFB_BLANK;
				color1 = color2;
				x1 = x2;
				y1 = y2;
				blanks = 1;
			} else
				blanks++;
		} else {
			if (blanks != 0) {
				MACHFB_BLANK;
				blanks = 0;
			}
			vidd_putc(adp, off + i, c, a);
		}
	}
	if (blanks != 0)
		MACHFB_BLANK;

#undef MACHFB_BLANK

	return (0);
}