#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t size; int /*<<< orphan*/ * data; scalar_t__ read; } ;
struct TYPE_8__ {int remaining; TYPE_4__ msg; int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ socket_t ;
struct TYPE_9__ {int size; } ;
typedef  TYPE_2__ netmessage_t ;

/* Variables and functions */
 int MAX_NETMESSAGE ; 
 int NMSG_ReadLong (TYPE_4__*) ; 
 void* WINS_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WinPrint (char*,...) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int Net_Receive( socket_t *sock, netmessage_t *msg ){
	int curread;

	if ( sock->remaining > 0 ) {
		curread = WINS_Read( sock->socket, &sock->msg.data[sock->msg.size], sock->remaining, NULL );
		if ( curread == -1 ) {
			WinPrint( "Net_Receive: read error\n" );
			return -1;
		} //end if
		sock->remaining -= curread;
		sock->msg.size += curread;
		if ( sock->remaining <= 0 ) {
			sock->remaining = 0;
			memcpy( msg, &sock->msg, sizeof( netmessage_t ) );
			sock->msg.size = 0;
			return msg->size - 4;
		} //end if
		return 0;
	} //end if
	sock->msg.size = WINS_Read( sock->socket, sock->msg.data, 4, NULL );
	if ( sock->msg.size == 0 ) {
		return 0;
	}
	if ( sock->msg.size == -1 ) {
		WinPrint( "Net_Receive: size header read error\n" );
		return -1;
	} //end if
	  //WinPrint("Net_Receive: message size header %d\n", msg->size);
	sock->msg.read = 0;
	sock->remaining = NMSG_ReadLong( &sock->msg );
	if ( sock->remaining == 0 ) {
		return 0;
	}
	if ( sock->remaining < 0 || sock->remaining > MAX_NETMESSAGE ) {
		WinPrint( "Net_Receive: invalid message size %d\n", sock->remaining );
		return -1;
	} //end if
	  //try to read the message
	curread = WINS_Read( sock->socket, &sock->msg.data[sock->msg.size], sock->remaining, NULL );
	if ( curread == -1 ) {
		WinPrint( "Net_Receive: read error\n" );
		return -1;
	} //end if
	sock->remaining -= curread;
	sock->msg.size += curread;
	if ( sock->remaining <= 0 ) {
		sock->remaining = 0;
		memcpy( msg, &sock->msg, sizeof( netmessage_t ) );
		sock->msg.size = 0;
		return msg->size - 4;
	} //end if
	  //the message has not been completely read yet
#ifdef _DEBUG
	printf( "++timo TODO: debug the Net_Receive on big size messages\n" );
#endif
	return 0;
}