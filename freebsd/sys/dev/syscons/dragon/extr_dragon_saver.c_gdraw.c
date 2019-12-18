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

/* Variables and functions */
 int cur_x ; 
 int cur_y ; 
 int gpset (int,int,int) ; 

__attribute__((used)) static int
gdraw(int dx, int dy, int val)
{
	int	i;
	int	set = 0;

	if (dx != 0) {
		i = cur_x;
		cur_x += dx;
		if (dx < 0) {
			i += dx;
			dx = -dx;
		}
		/* horizontal line */
		for (; dx >= 0; --dx, ++i) {
			set |= gpset(i, cur_y, val);
		} 
	}
	else {	/* dy != 0 */
		i = cur_y;
		cur_y += dy;
		if (dy < 0) {
			i += dy;
			dy = -dy;
		}
		/* vertical line */
		for (; dy >= 0; --dy, ++i) {
			set |= gpset(cur_x, i, val);
		} 
	}
	return set;
}