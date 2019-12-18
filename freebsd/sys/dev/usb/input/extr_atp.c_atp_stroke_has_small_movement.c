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
typedef  scalar_t__ u_int ;
typedef  int boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  instantaneous_dy; int /*<<< orphan*/  instantaneous_dx; } ;
typedef  TYPE_1__ atp_stroke_t ;

/* Variables and functions */
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 scalar_t__ atp_small_movement_threshold ; 

__attribute__((used)) static boolean_t
atp_stroke_has_small_movement(const atp_stroke_t *strokep)
{
	return (((u_int)abs(strokep->instantaneous_dx) <=
		 atp_small_movement_threshold) &&
		((u_int)abs(strokep->instantaneous_dy) <=
		 atp_small_movement_threshold));
}