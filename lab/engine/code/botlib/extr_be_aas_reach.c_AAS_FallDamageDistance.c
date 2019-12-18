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
struct TYPE_2__ {float phys_gravity; } ;

/* Variables and functions */
 TYPE_1__ aassettings ; 
 float sqrt (int) ; 

int AAS_FallDamageDistance(void)
{
	float maxzvelocity, gravity, t;

	maxzvelocity = sqrt(30 * 10000);
	gravity = aassettings.phys_gravity;
	t = maxzvelocity / gravity;
	return 0.5 * gravity * t * t;
}