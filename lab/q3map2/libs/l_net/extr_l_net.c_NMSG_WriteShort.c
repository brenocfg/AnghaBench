#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int* data; } ;
typedef  TYPE_1__ netmessage_t ;

/* Variables and functions */
 int MAX_NETMESSAGE ; 
 int /*<<< orphan*/  WinPrint (char*) ; 

void NMSG_WriteShort( netmessage_t *msg, int c ){
	if ( c < ( (short)0x8000 ) || c > (short)0x7fff ) {
		WinPrint( "NMSG_WriteShort: range error" );
	}

	if ( msg->size + 2 >= MAX_NETMESSAGE ) {
		WinPrint( "NMSG_WriteShort: overflow\n" );
		return;
	} //end if
	msg->data[msg->size] = c & 0xff;
	msg->data[msg->size + 1] = c >> 8;
	msg->size += 2;
}