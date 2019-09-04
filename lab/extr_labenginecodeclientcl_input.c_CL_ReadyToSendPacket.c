#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_16__ {scalar_t__ type; } ;
struct TYPE_15__ {TYPE_2__* outPackets; } ;
struct TYPE_14__ {scalar_t__ integer; } ;
struct TYPE_13__ {int integer; } ;
struct TYPE_9__ {int outgoingSequence; TYPE_8__ remoteAddress; } ;
struct TYPE_12__ {scalar_t__ state; int lastPacketSentTime; TYPE_1__ netchan; scalar_t__* downloadTempName; scalar_t__ demoplaying; } ;
struct TYPE_11__ {int realtime; } ;
struct TYPE_10__ {int p_realtime; } ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 scalar_t__ CA_CINEMATIC ; 
 scalar_t__ CA_PRIMED ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 scalar_t__ NA_LOOPBACK ; 
 int PACKET_MASK ; 
 scalar_t__ Sys_IsLANAddress (TYPE_8__) ; 
 TYPE_7__ cl ; 
 TYPE_6__* cl_lanForcePackets ; 
 TYPE_5__* cl_maxpackets ; 
 TYPE_4__ clc ; 
 TYPE_3__ cls ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean CL_ReadyToSendPacket( void ) {
	int		oldPacketNum;
	int		delta;

	// don't send anything if playing back a demo
	if ( clc.demoplaying || clc.state == CA_CINEMATIC ) {
		return qfalse;
	}

	// If we are downloading, we send no less than 50ms between packets
	if ( *clc.downloadTempName &&
		cls.realtime - clc.lastPacketSentTime < 50 ) {
		return qfalse;
	}

	// if we don't have a valid gamestate yet, only send
	// one packet a second
	if ( clc.state != CA_ACTIVE && 
		clc.state != CA_PRIMED && 
		!*clc.downloadTempName &&
		cls.realtime - clc.lastPacketSentTime < 1000 ) {
		return qfalse;
	}

	// send every frame for loopbacks
	if ( clc.netchan.remoteAddress.type == NA_LOOPBACK ) {
		return qtrue;
	}

	// send every frame for LAN
	if ( cl_lanForcePackets->integer && Sys_IsLANAddress( clc.netchan.remoteAddress ) ) {
		return qtrue;
	}

	// check for exceeding cl_maxpackets
	if ( cl_maxpackets->integer < 15 ) {
		Cvar_Set( "cl_maxpackets", "15" );
	} else if ( cl_maxpackets->integer > 125 ) {
		Cvar_Set( "cl_maxpackets", "125" );
	}
	oldPacketNum = (clc.netchan.outgoingSequence - 1) & PACKET_MASK;
	delta = cls.realtime -  cl.outPackets[ oldPacketNum ].p_realtime;
	if ( delta < 1000 / cl_maxpackets->integer ) {
		// the accumulated commands will go out in the next packet
		return qfalse;
	}

	return qtrue;
}