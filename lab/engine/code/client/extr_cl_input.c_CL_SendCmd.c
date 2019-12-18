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
struct TYPE_10__ {scalar_t__ integer; } ;
struct TYPE_9__ {scalar_t__ integer; } ;
struct TYPE_8__ {scalar_t__ state; } ;
struct TYPE_7__ {scalar_t__ integer; } ;
struct TYPE_6__ {scalar_t__ integer; } ;

/* Variables and functions */
 scalar_t__ CA_CONNECTED ; 
 int /*<<< orphan*/  CL_CreateNewCommands () ; 
 int /*<<< orphan*/  CL_ReadyToSendPacket () ; 
 int /*<<< orphan*/  CL_WritePacket () ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 TYPE_5__* cl_paused ; 
 TYPE_4__* cl_showSend ; 
 TYPE_3__ clc ; 
 TYPE_2__* com_sv_running ; 
 TYPE_1__* sv_paused ; 

void CL_SendCmd( void ) {
	// don't send any message if not connected
	if ( clc.state < CA_CONNECTED ) {
		return;
	}

	// don't send commands if paused
	if ( com_sv_running->integer && sv_paused->integer && cl_paused->integer ) {
		return;
	}

	// we create commands even if a demo is playing,
	CL_CreateNewCommands();

	// don't send a packet if the last packet was sent too recently
	if ( !CL_ReadyToSendPacket() ) {
		if ( cl_showSend->integer ) {
			Com_Printf( ". " );
		}
		return;
	}

	CL_WritePacket();
}