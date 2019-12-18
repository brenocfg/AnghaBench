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
typedef  int u_short ;
struct TYPE_4__ {int* bg; } ;
struct TYPE_5__ {TYPE_1__ curs_attr; } ;
typedef  TYPE_2__ scr_stat ;

/* Variables and functions */
 int nitems (int*) ; 
 int vga_flipattr (int,int) ; 

__attribute__((used)) static u_short
vga_cursorattr_adj(scr_stat *scp, u_short a, int blink)
{
	int i;
	u_short bg, bgmask, fg, newbg;

	/*
	 * The cursor attribute is usually that of the underlying char
	 * with only the bg changed, to the first preferred color that
	 * differs from both the fg and bg.  If there is no such color,
	 * use reverse video.
	 */
	bgmask = blink ? 0x7000 : 0xf000;
	bg = a & bgmask;
	fg = a & 0x0f00;
	for (i = 0; i < nitems(scp->curs_attr.bg); i++) {
		newbg = (scp->curs_attr.bg[i] << 12) & bgmask;
		if (newbg != bg && newbg != (fg << 4))
			break;
	}
	if (i == nitems(scp->curs_attr.bg))
		return (vga_flipattr(a, blink));
	return (fg | newbg | (blink ? a & 0x8000 : 0));
}