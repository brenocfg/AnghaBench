#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netadr_t ;
struct TYPE_10__ {int cursize; int readcount; scalar_t__ data; } ;
typedef  TYPE_1__ msg_t ;
struct TYPE_13__ {int /*<<< orphan*/  remoteAddress; } ;
struct TYPE_12__ {scalar_t__ state; int /*<<< orphan*/  demowaiting; scalar_t__ demorecording; int /*<<< orphan*/  lastPacketTime; int /*<<< orphan*/  serverMessageSequence; TYPE_7__ netchan; } ;
struct TYPE_11__ {int /*<<< orphan*/  realtime; } ;

/* Variables and functions */
 scalar_t__ CA_CONNECTED ; 
 int /*<<< orphan*/  CL_ConnectionlessPacket (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CL_Netchan_Process (TYPE_7__*,TYPE_1__*) ; 
 int /*<<< orphan*/  CL_ParseServerMessage (TYPE_1__*) ; 
 int /*<<< orphan*/  CL_WriteDemoMessage (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Com_DPrintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LittleLong (int) ; 
 int /*<<< orphan*/  NET_AdrToStringwPort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_CompareAdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ clc ; 
 TYPE_2__ cls ; 

void CL_PacketEvent( netadr_t from, msg_t *msg ) {
	int		headerBytes;

	clc.lastPacketTime = cls.realtime;

	if ( msg->cursize >= 4 && *(int *)msg->data == -1 ) {
		CL_ConnectionlessPacket( from, msg );
		return;
	}

	if ( clc.state < CA_CONNECTED ) {
		return;		// can't be a valid sequenced packet
	}

	if ( msg->cursize < 4 ) {
		Com_Printf ("%s: Runt packet\n", NET_AdrToStringwPort( from ));
		return;
	}

	//
	// packet from server
	//
	if ( !NET_CompareAdr( from, clc.netchan.remoteAddress ) ) {
		Com_DPrintf ("%s:sequenced packet without connection\n"
			, NET_AdrToStringwPort( from ) );
		// FIXME: send a client disconnect?
		return;
	}

	if (!CL_Netchan_Process( &clc.netchan, msg) ) {
		return;		// out of order, duplicated, etc
	}

	// the header is different lengths for reliable and unreliable messages
	headerBytes = msg->readcount;

	// track the last message received so it can be returned in 
	// client messages, allowing the server to detect a dropped
	// gamestate
	clc.serverMessageSequence = LittleLong( *(int *)msg->data );

	clc.lastPacketTime = cls.realtime;
	CL_ParseServerMessage( msg );

	//
	// we don't know if it is ok to save a demo message until
	// after we have parsed the frame
	//
	if ( clc.demorecording && !clc.demowaiting ) {
		CL_WriteDemoMessage( msg, headerBytes );
	}
}