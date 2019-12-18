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
struct x_bound {int x_cur; int x_min; int x_max; } ;

/* Variables and functions */
 int hz ; 

__attribute__((used)) static int
get_bounded(struct x_bound *v, int t_min)
{
	int x;

	x = v->x_cur;
	if (x < v->x_min)
		x = v->x_min;
	else if (x > v->x_max)
		x = v->x_max;
	if (t_min) {
		x = x * hz / 1000;	/* convert to ticks */
		if (x < t_min)
			x = t_min;
	}
	return x;
}