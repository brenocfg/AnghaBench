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

void NMSG_WriteFloat( netmessage_t *msg, float c ){
	if ( msg->size + 4 >= MAX_NETMESSAGE ) {
		WinPrint( "NMSG_WriteLong: overflow\n" );
		return;
	} //end if
	msg->data[msg->size] = *( (int *)&c ) & 0xff;
	msg->data[msg->size + 1] = ( *( (int *)&c ) >> 8 ) & 0xff;
	msg->data[msg->size + 2] = ( *( (int *)&c ) >> 16 ) & 0xff;
	msg->data[msg->size + 3] = *( (int *)&c ) >> 24;
	msg->size += 4;
}