#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int u_int ;
struct TYPE_7__ {int xsize; int ysize; TYPE_2__* sc; } ;
struct TYPE_6__ {TYPE_1__* adp; } ;
struct TYPE_5__ {uintptr_t va_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISTEXTSC (TYPE_3__*) ; 
 int KERNBASE ; 
 scalar_t__ atomic_cmpset_rel_int (int*,int,int) ; 
 int ec_scroffset ; 
 TYPE_3__ main_console ; 
 int pmap_get_map_low () ; 
 int /*<<< orphan*/ * sc_console ; 
 int sc_kattr () ; 

__attribute__((used)) static void
ec_putc(int c)
{
	uintptr_t fb;
	u_short *scrptr;
	u_int ind;
	int attr, column, mysize, width, xsize, yborder, ysize;

	if (c < 0 || c > 0xff || c == '\a')
		return;
	if (sc_console == NULL) {
#if !defined(__amd64__) && !defined(__i386__)
		return;
#else
		/*
		 * This is enough for ec_putc() to work very early on x86
		 * if the kernel starts in normal color text mode.
		 */
#ifdef __amd64__
		fb = KERNBASE + 0xb8000;
#else /* __i386__ */
		fb = pmap_get_map_low() + 0xb8000;
#endif
		xsize = 80;
		ysize = 25;
#endif
	} else {
		if (!ISTEXTSC(&main_console))
			return;
		fb = main_console.sc->adp->va_window;
		xsize = main_console.xsize;
		ysize = main_console.ysize;
	}
	yborder = ysize / 5;
	scrptr = (u_short *)(void *)fb + xsize * yborder;
	mysize = xsize * (ysize - 2 * yborder);
	do {
		ind = ec_scroffset;
		column = ind % xsize;
		width = (c == '\b' ? -1 : c == '\t' ? (column + 8) & ~7 :
		    c == '\r' ? -column : c == '\n' ? xsize - column : 1);
		if (width == 0 || (width < 0 && ind < -width))
			return;
	} while (atomic_cmpset_rel_int(&ec_scroffset, ind, ind + width) == 0);
	if (c == '\b' || c == '\r')
		return;
	if (c == '\n')
		ind += xsize;	/* XXX clearing from new pos is not atomic */

	attr = sc_kattr();
	if (c == '\t' || c == '\n')
		c = ' ';
	do
		scrptr[ind++ % mysize] = (attr << 8) | c;
	while (--width != 0);
}