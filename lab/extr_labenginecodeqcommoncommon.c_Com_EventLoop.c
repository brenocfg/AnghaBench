#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int evType; int evTime; scalar_t__ evPtr; int /*<<< orphan*/  evValue2; int /*<<< orphan*/  evValue; } ;
typedef  TYPE_1__ sysEvent_t ;
typedef  int /*<<< orphan*/  netadr_t ;
typedef  int /*<<< orphan*/  msg_t ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  bufData ;
struct TYPE_5__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_CharEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_JoystickEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CL_KeyEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CL_MouseEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CL_PacketEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Cbuf_AddText (char*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ Com_GetEvent () ; 
 int /*<<< orphan*/  Com_RunAndTimeServerPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int MAX_MSGLEN ; 
 int /*<<< orphan*/  MSG_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ NET_GetLoopPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NS_CLIENT ; 
 int /*<<< orphan*/  NS_SERVER ; 
#define  SE_CHAR 132 
#define  SE_CONSOLE 131 
#define  SE_JOYSTICK_AXIS 130 
#define  SE_KEY 129 
#define  SE_MOUSE 128 
 int SE_NONE ; 
 int /*<<< orphan*/  Z_Free (scalar_t__) ; 
 TYPE_2__* com_sv_running ; 

int Com_EventLoop( void ) {
	sysEvent_t	ev;
	netadr_t	evFrom;
	byte		bufData[MAX_MSGLEN];
	msg_t		buf;

	MSG_Init( &buf, bufData, sizeof( bufData ) );

	while ( 1 ) {
		ev = Com_GetEvent();

		// if no more events are available
		if ( ev.evType == SE_NONE ) {
			// manually send packet events for the loopback channel
			while ( NET_GetLoopPacket( NS_CLIENT, &evFrom, &buf ) ) {
				CL_PacketEvent( evFrom, &buf );
			}

			while ( NET_GetLoopPacket( NS_SERVER, &evFrom, &buf ) ) {
				// if the server just shut down, flush the events
				if ( com_sv_running->integer ) {
					Com_RunAndTimeServerPacket( &evFrom, &buf );
				}
			}

			return ev.evTime;
		}


		switch(ev.evType)
		{
			case SE_KEY:
				CL_KeyEvent( ev.evValue, ev.evValue2, ev.evTime );
			break;
			case SE_CHAR:
				CL_CharEvent( ev.evValue );
			break;
			case SE_MOUSE:
				CL_MouseEvent( ev.evValue, ev.evValue2, ev.evTime );
			break;
			case SE_JOYSTICK_AXIS:
				CL_JoystickEvent( ev.evValue, ev.evValue2, ev.evTime );
			break;
			case SE_CONSOLE:
				Cbuf_AddText( (char *)ev.evPtr );
				Cbuf_AddText( "\n" );
			break;
			default:
				Com_Error( ERR_FATAL, "Com_EventLoop: bad event type %i", ev.evType );
			break;
		}

		// free any block data
		if ( ev.evPtr ) {
			Z_Free( ev.evPtr );
		}
	}

	return 0;	// never reached
}