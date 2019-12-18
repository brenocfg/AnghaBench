#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ socket_t ;
struct TYPE_7__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ netmessage_t ;

/* Variables and functions */
 int /*<<< orphan*/  NMSG_WriteLong (TYPE_2__*,int) ; 
 int WINS_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int Net_Send( socket_t *sock, netmessage_t *msg ){
	int size;

	size = msg->size;
	msg->size = 0;
	NMSG_WriteLong( msg, size - 4 );
	msg->size = size;
	//WinPrint("Net_Send: message of size %d\n", sendmsg.size);
	return WINS_Write( sock->socket, msg->data, msg->size, NULL );
}