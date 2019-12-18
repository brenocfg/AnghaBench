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
typedef  int /*<<< orphan*/  string ;
struct TYPE_3__ {int read; int size; int* data; int /*<<< orphan*/  readoverflow; } ;
typedef  TYPE_1__ netmessage_t ;

/* Variables and functions */
 int /*<<< orphan*/  WinPrint (char*) ; 
 int /*<<< orphan*/  qtrue ; 

char *NMSG_ReadString( netmessage_t *msg ){
	static char string[2048];
	int l, c;

	l = 0;
	do
	{
		if ( msg->read + 1 > msg->size ) {
			msg->readoverflow = qtrue;
			WinPrint( "NMSG_ReadString: read overflow\n" );
			string[l] = 0;
			return string;
		} //end if
		c = msg->data[msg->read];
		msg->read++;
		if ( c == 0 ) {
			break;
		}
		string[l] = c;
		l++;
	} while ( l < sizeof( string ) - 1 );
	string[l] = 0;
	return string;
}