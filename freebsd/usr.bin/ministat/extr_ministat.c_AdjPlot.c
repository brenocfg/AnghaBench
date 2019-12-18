#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct plot {double min; double max; double span; double dx; double width; double x0; } ;

/* Variables and functions */
 struct plot plot ; 

__attribute__((used)) static void
AdjPlot(double a)
{
	struct plot *pl;

	pl = &plot;
	if (a < pl->min)
		pl->min = a;
	if (a > pl->max)
		pl->max = a;
	pl->span = pl->max - pl->min;
	pl->dx = pl->span / (pl->width - 1.0);
	pl->x0 = pl->min - .5 * pl->dx;
}