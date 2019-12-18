#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_adapter_t ;
typedef  int fp16_t ;
struct TYPE_2__ {unsigned int x; unsigned int y; unsigned int vx; unsigned int vy; } ;

/* Variables and functions */
 unsigned int FOCI ; 
 int /*<<< orphan*/  FP16toI (int) ; 
 int ItoFP16 (int) ; 
 unsigned int banksize ; 
 int fp16_add (int,int) ; 
 int /*<<< orphan*/  fp16_cos (int) ; 
 int fp16_div (int,int) ; 
 int fp16_mul (int,int) ; 
 int fp16_sqrt (int) ; 
 int fp16_sub (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* plasma_foci ; 
 unsigned int scrh ; 
 unsigned int scrw ; 
 int /*<<< orphan*/ * vid ; 
 int /*<<< orphan*/  vidd_set_win_org (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
plasma_update(video_adapter_t *adp)
{
	unsigned int x, y;	/* coordinates */
	signed int dx, dy;	/* horizontal / vertical distance */
	fp16_t sqd, d;		/* square of distance and distance */
	fp16_t m;		/* magnitude */
	unsigned int org, off;	/* origin and offset */
	unsigned int i;		/* loop index */

	/* switch to bank 0 */
	vidd_set_win_org(adp, 0);
	/* for each scan line */
	for (y = org = off = 0; y < scrh; ++y) {
		/* for each pixel on scan line */
		for (x = 0; x < scrw; ++x, ++off) {
			/* for each focus */
			for (i = m = 0; i < FOCI; ++i) {
				dx = x - plasma_foci[i].x;
				dy = y - plasma_foci[i].y;
				sqd = ItoFP16(dx * dx + dy * dy);
				d = fp16_sqrt(sqd);
				/* divide by 4 to stretch out the pattern */
				m = fp16_sub(m, fp16_cos(d / 4));
			}
			/*
			 * m is now in the range +/- FOCI, but we need a
			 * value between 0 and 255.  We scale to +/- 127
			 * and add 127, which moves it into the range [0,
			 * 254].
			 */
			m = fp16_mul(m, ItoFP16(127));
			m = fp16_div(m, ItoFP16(FOCI));
			m = fp16_add(m, ItoFP16(127));
			/* switch banks if necessary */
			if (off > banksize) {
				off -= banksize;
				org += banksize;
				vidd_set_win_org(adp, org);
			}
			/* plot */
			vid[off] = FP16toI(m);
		}
	}
	/* now move the foci */
	for (i = 0; i < FOCI; ++i) {
		plasma_foci[i].x += plasma_foci[i].vx;
		if (plasma_foci[i].x < 0) {
			/* bounce against left wall */
			plasma_foci[i].vx = -plasma_foci[i].vx;
			plasma_foci[i].x = -plasma_foci[i].x;
		} else if (plasma_foci[i].x >= scrw) {
			/* bounce against right wall */
			plasma_foci[i].vx = -plasma_foci[i].vx;
			plasma_foci[i].x = scrw - (plasma_foci[i].x - scrw);
		}
		plasma_foci[i].y += plasma_foci[i].vy;
		if (plasma_foci[i].y < 0) {
			/* bounce against ceiling */
			plasma_foci[i].vy = -plasma_foci[i].vy;
			plasma_foci[i].y = -plasma_foci[i].y;
		} else if (plasma_foci[i].y >= scrh) {
			/* bounce against floor */
			plasma_foci[i].vy = -plasma_foci[i].vy;
			plasma_foci[i].y = scrh - (plasma_foci[i].y - scrh);
		}
	}
}