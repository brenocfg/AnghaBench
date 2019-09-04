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
struct TYPE_3__ {int read; int size; int* data; int /*<<< orphan*/  readoverflow; } ;
typedef  TYPE_1__ netmessage_t ;

/* Variables and functions */
 int /*<<< orphan*/  WinPrint (char*) ; 
 int /*<<< orphan*/  qtrue ; 

int NMSG_ReadLong( netmessage_t *msg ){
	int c;

	if ( msg->read + 4 > msg->size ) {
		msg->readoverflow = qtrue;
		WinPrint( "NMSG_ReadLong: read overflow\n" );
		return 0;
	} //end if
	c = msg->data[msg->read]
		+ ( msg->data[msg->read + 1] << 8 )
		+ ( msg->data[msg->read + 2] << 16 )
		+ ( msg->data[msg->read + 3] << 24 );
	msg->read += 4;
	return c;
}