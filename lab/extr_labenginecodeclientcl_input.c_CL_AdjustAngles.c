#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {float* viewangles; } ;
struct TYPE_13__ {double value; } ;
struct TYPE_12__ {float value; } ;
struct TYPE_11__ {float value; } ;
struct TYPE_10__ {double frametime; } ;
struct TYPE_9__ {scalar_t__ active; } ;
struct TYPE_8__ {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 float CL_KeyState (int /*<<< orphan*/ *) ; 
 size_t PITCH ; 
 size_t YAW ; 
 TYPE_7__ cl ; 
 TYPE_6__* cl_anglespeedkey ; 
 TYPE_5__* cl_pitchspeed ; 
 TYPE_4__* cl_yawspeed ; 
 TYPE_3__ cls ; 
 int /*<<< orphan*/  in_left ; 
 int /*<<< orphan*/  in_lookdown ; 
 int /*<<< orphan*/  in_lookup ; 
 int /*<<< orphan*/  in_right ; 
 TYPE_2__ in_speed ; 
 TYPE_1__ in_strafe ; 

void CL_AdjustAngles( void ) {
	float	speed;
	
	if ( in_speed.active ) {
		speed = 0.001 * cls.frametime * cl_anglespeedkey->value;
	} else {
		speed = 0.001 * cls.frametime;
	}

	if ( !in_strafe.active ) {
		cl.viewangles[YAW] -= speed*cl_yawspeed->value*CL_KeyState (&in_right);
		cl.viewangles[YAW] += speed*cl_yawspeed->value*CL_KeyState (&in_left);
	}

	cl.viewangles[PITCH] -= speed*cl_pitchspeed->value * CL_KeyState (&in_lookup);
	cl.viewangles[PITCH] += speed*cl_pitchspeed->value * CL_KeyState (&in_lookdown);
}