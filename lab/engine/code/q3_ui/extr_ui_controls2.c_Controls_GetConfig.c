#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int bind1; int bind2; int /*<<< orphan*/  command; int /*<<< orphan*/  label; } ;
typedef  TYPE_9__ bind_t ;
struct TYPE_20__ {void* curvalue; } ;
struct TYPE_19__ {void* curvalue; } ;
struct TYPE_18__ {void* curvalue; } ;
struct TYPE_17__ {void* curvalue; } ;
struct TYPE_16__ {void* curvalue; } ;
struct TYPE_15__ {void* curvalue; } ;
struct TYPE_14__ {void* curvalue; } ;
struct TYPE_13__ {int curvalue; } ;
struct TYPE_12__ {TYPE_8__ freelook; TYPE_7__ joythreshold; TYPE_6__ joyenable; TYPE_5__ sensitivity; TYPE_4__ autoswitch; TYPE_3__ alwaysrun; TYPE_2__ smoothmouse; TYPE_1__ invertmouse; } ;

/* Variables and functions */
 scalar_t__ Controls_GetCvarValue (char*) ; 
 int /*<<< orphan*/  Controls_GetKeyAssignment (int /*<<< orphan*/ ,int*) ; 
 void* UI_ClampCvar (float,int,scalar_t__) ; 
 TYPE_9__* g_bindings ; 
 TYPE_10__ s_controls ; 

__attribute__((used)) static void Controls_GetConfig( void )
{
	int		i;
	int		twokeys[2];
	bind_t*	bindptr;

	// put the bindings into a local store
	bindptr = g_bindings;

	// iterate each command, get its numeric binding
	for (i=0; ;i++,bindptr++)
	{
		if (!bindptr->label)
			break;

		Controls_GetKeyAssignment(bindptr->command, twokeys);

		bindptr->bind1 = twokeys[0];
		bindptr->bind2 = twokeys[1];
	}

	s_controls.invertmouse.curvalue  = Controls_GetCvarValue( "m_pitch" ) < 0;
	s_controls.smoothmouse.curvalue  = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "m_filter" ) );
	s_controls.alwaysrun.curvalue    = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "cl_run" ) );
	s_controls.autoswitch.curvalue   = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "cg_autoswitch" ) );
	s_controls.sensitivity.curvalue  = UI_ClampCvar( 2, 30, Controls_GetCvarValue( "sensitivity" ) );
	s_controls.joyenable.curvalue    = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "in_joystick" ) );
	s_controls.joythreshold.curvalue = UI_ClampCvar( 0.05f, 0.75f, Controls_GetCvarValue( "joy_threshold" ) );
	s_controls.freelook.curvalue     = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "cl_freelook" ) );
}