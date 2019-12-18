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
struct TYPE_2__ {float phys_gravity; float phys_maxvelocity; double rs_maxjumpfallheight; } ;

/* Variables and functions */
 TYPE_1__ aassettings ; 
 float sqrt (double) ; 

float AAS_MaxJumpDistance(float phys_jumpvel)
{
	float phys_gravity, phys_maxvelocity, t;

	phys_gravity = aassettings.phys_gravity;
	phys_maxvelocity = aassettings.phys_maxvelocity;
	//time a player takes to fall the height
	t = sqrt(aassettings.rs_maxjumpfallheight / (0.5 * phys_gravity));
   //maximum distance
	return phys_maxvelocity * (t + phys_jumpvel / phys_gravity);
}