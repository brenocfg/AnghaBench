#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int timeoutcount; } ;
struct TYPE_9__ {int value; } ;
struct TYPE_8__ {scalar_t__ state; int lastPacketTime; } ;
struct TYPE_7__ {int realtime; } ;
struct TYPE_6__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 scalar_t__ CA_CINEMATIC ; 
 scalar_t__ CA_CONNECTED ; 
 int /*<<< orphan*/  CL_CheckPaused () ; 
 int /*<<< orphan*/  CL_Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 TYPE_5__ cl ; 
 TYPE_4__* cl_timeout ; 
 TYPE_3__ clc ; 
 TYPE_2__ cls ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__* sv_paused ; 

void CL_CheckTimeout( void ) {
	//
	// check timeout
	//
	if ( ( !CL_CheckPaused() || !sv_paused->integer ) 
		&& clc.state >= CA_CONNECTED && clc.state != CA_CINEMATIC
	    && cls.realtime - clc.lastPacketTime > cl_timeout->value*1000) {
		if (++cl.timeoutcount > 5) {	// timeoutcount saves debugger
			Com_Printf ("\nServer connection timed out.\n");
			CL_Disconnect( qtrue );
			return;
		}
	} else {
		cl.timeoutcount = 0;
	}
}