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
struct termp {int defrmargin; size_t lastrmargin; int maxrmargin; TYPE_1__* tcol; } ;
struct TYPE_2__ {int rmargin; } ;

/* Variables and functions */

__attribute__((used)) static void
ascii_setwidth(struct termp *p, int iop, int width)
{

	width /= 24;
	p->tcol->rmargin = p->defrmargin;
	if (iop > 0)
		p->defrmargin += width;
	else if (iop == 0)
		p->defrmargin = width ? (size_t)width : p->lastrmargin;
	else if (p->defrmargin > (size_t)width)
		p->defrmargin -= width;
	else
		p->defrmargin = 0;
	if (p->defrmargin > 1000)
		p->defrmargin = 1000;
	p->lastrmargin = p->tcol->rmargin;
	p->tcol->rmargin = p->maxrmargin = p->defrmargin;
}