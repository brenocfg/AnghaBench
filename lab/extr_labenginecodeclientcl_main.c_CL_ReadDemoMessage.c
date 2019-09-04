#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cursize; int maxsize; int* data; scalar_t__ readcount; } ;
typedef  TYPE_1__ msg_t ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  bufData ;
struct TYPE_8__ {int /*<<< orphan*/  lastPacketTime; int /*<<< orphan*/  demofile; void* serverMessageSequence; } ;
struct TYPE_7__ {int /*<<< orphan*/  realtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_DemoCompleted () ; 
 int /*<<< orphan*/  CL_ParseServerMessage (TYPE_1__*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int FS_Read (int*,int,int /*<<< orphan*/ ) ; 
 void* LittleLong (int) ; 
 int MAX_MSGLEN ; 
 int /*<<< orphan*/  MSG_Init (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 TYPE_3__ clc ; 
 TYPE_2__ cls ; 

void CL_ReadDemoMessage( void ) {
	int			r;
	msg_t		buf;
	byte		bufData[ MAX_MSGLEN ];
	int			s;

	if ( !clc.demofile ) {
		CL_DemoCompleted ();
		return;
	}

	// get the sequence number
	r = FS_Read( &s, 4, clc.demofile);
	if ( r != 4 ) {
		CL_DemoCompleted ();
		return;
	}
	clc.serverMessageSequence = LittleLong( s );

	// init the message
	MSG_Init( &buf, bufData, sizeof( bufData ) );

	// get the length
	r = FS_Read (&buf.cursize, 4, clc.demofile);
	if ( r != 4 ) {
		CL_DemoCompleted ();
		return;
	}
	buf.cursize = LittleLong( buf.cursize );
	if ( buf.cursize == -1 ) {
		CL_DemoCompleted ();
		return;
	}
	if ( buf.cursize > buf.maxsize ) {
		Com_Error (ERR_DROP, "CL_ReadDemoMessage: demoMsglen > MAX_MSGLEN");
	}
	r = FS_Read( buf.data, buf.cursize, clc.demofile );
	if ( r != buf.cursize ) {
		Com_Printf( "Demo file was truncated.\n");
		CL_DemoCompleted ();
		return;
	}

	clc.lastPacketTime = cls.realtime;
	buf.readcount = 0;
	CL_ParseServerMessage( &buf );
}