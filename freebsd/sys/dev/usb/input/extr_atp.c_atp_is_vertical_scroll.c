#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int boolean_t ;
struct TYPE_3__ {int cum_movement_y; int cum_movement_x; } ;
typedef  TYPE_1__ atp_stroke_t ;

/* Variables and functions */
 int abs (int) ; 
 int atp_slide_min_movement ; 

__attribute__((used)) static boolean_t
atp_is_vertical_scroll(const atp_stroke_t *strokep)
{
	if (abs(strokep->cum_movement_y) < atp_slide_min_movement)
		return (false);
	if (strokep->cum_movement_x == 0)
		return (true);
	return (abs(strokep->cum_movement_y / strokep->cum_movement_x) >= 4);
}