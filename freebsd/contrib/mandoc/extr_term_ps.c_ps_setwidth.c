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
struct termp {TYPE_1__* ps; } ;
struct TYPE_2__ {size_t width; size_t lastwidth; } ;

/* Variables and functions */

__attribute__((used)) static void
ps_setwidth(struct termp *p, int iop, int width)
{
	size_t	 lastwidth;

	lastwidth = p->ps->width;
	if (iop > 0)
		p->ps->width += width;
	else if (iop == 0)
		p->ps->width = width ? (size_t)width : p->ps->lastwidth;
	else if (p->ps->width > (size_t)width)
		p->ps->width -= width;
	else
		p->ps->width = 0;
	p->ps->lastwidth = lastwidth;
}