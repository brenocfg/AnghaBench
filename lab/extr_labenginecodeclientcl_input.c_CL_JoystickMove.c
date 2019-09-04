#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_17__ ;
typedef  struct TYPE_25__   TYPE_16__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_27__ {void* upmove; void* forwardmove; void* rightmove; int /*<<< orphan*/  buttons; } ;
typedef  TYPE_1__ usercmd_t ;
struct TYPE_35__ {float value; } ;
struct TYPE_34__ {size_t integer; } ;
struct TYPE_33__ {float value; } ;
struct TYPE_32__ {size_t integer; } ;
struct TYPE_31__ {float value; } ;
struct TYPE_30__ {size_t integer; } ;
struct TYPE_29__ {float value; } ;
struct TYPE_28__ {size_t integer; } ;
struct TYPE_26__ {float* joystickAxis; float* viewangles; } ;
struct TYPE_25__ {double value; } ;
struct TYPE_24__ {int integer; } ;
struct TYPE_23__ {double frametime; } ;
struct TYPE_22__ {int active; } ;
struct TYPE_21__ {int /*<<< orphan*/  active; } ;
struct TYPE_20__ {float value; } ;
struct TYPE_19__ {size_t integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTON_WALKING ; 
 void* ClampChar (int /*<<< orphan*/ ) ; 
 size_t PITCH ; 
 size_t YAW ; 
 TYPE_17__ cl ; 
 TYPE_16__* cl_anglespeedkey ; 
 TYPE_15__* cl_run ; 
 TYPE_14__ cls ; 
 scalar_t__ in_mlooking ; 
 TYPE_13__ in_speed ; 
 TYPE_12__ in_strafe ; 
 TYPE_11__* j_forward ; 
 TYPE_10__* j_forward_axis ; 
 TYPE_9__* j_pitch ; 
 TYPE_8__* j_pitch_axis ; 
 TYPE_7__* j_side ; 
 TYPE_6__* j_side_axis ; 
 TYPE_5__* j_up ; 
 TYPE_4__* j_up_axis ; 
 TYPE_3__* j_yaw ; 
 TYPE_2__* j_yaw_axis ; 

void CL_JoystickMove( usercmd_t *cmd ) {
	float	anglespeed;

	float yaw     = j_yaw->value     * cl.joystickAxis[j_yaw_axis->integer];
	float right   = j_side->value    * cl.joystickAxis[j_side_axis->integer];
	float forward = j_forward->value * cl.joystickAxis[j_forward_axis->integer];
	float pitch   = j_pitch->value   * cl.joystickAxis[j_pitch_axis->integer];
	float up      = j_up->value      * cl.joystickAxis[j_up_axis->integer];

	if ( !(in_speed.active ^ cl_run->integer) ) {
		cmd->buttons |= BUTTON_WALKING;
	}

	if ( in_speed.active ) {
		anglespeed = 0.001 * cls.frametime * cl_anglespeedkey->value;
	} else {
		anglespeed = 0.001 * cls.frametime;
	}

	if ( !in_strafe.active ) {
		cl.viewangles[YAW] += anglespeed * yaw;
		cmd->rightmove = ClampChar( cmd->rightmove + (int)right );
	} else {
		cl.viewangles[YAW] += anglespeed * right;
		cmd->rightmove = ClampChar( cmd->rightmove + (int)yaw );
	}

	if ( in_mlooking ) {
		cl.viewangles[PITCH] += anglespeed * forward;
		cmd->forwardmove = ClampChar( cmd->forwardmove + (int)pitch );
	} else {
		cl.viewangles[PITCH] += anglespeed * pitch;
		cmd->forwardmove = ClampChar( cmd->forwardmove + (int)forward );
	}

	cmd->upmove = ClampChar( cmd->upmove + (int)up );
}