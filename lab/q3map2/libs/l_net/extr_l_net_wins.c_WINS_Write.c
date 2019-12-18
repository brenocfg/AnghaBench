#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sockaddr_s {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  WINS_ErrorMessage (scalar_t__) ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 int /*<<< orphan*/  WinPrint (char*,int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int send (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sendto (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

int WINS_Write( int socket, byte *buf, int len, struct sockaddr_s *addr ){
	int ret, written;

	if ( addr ) {
		written = 0;
		while ( written < len )
		{
			ret = sendto( socket, &buf[written], len - written, 0, (struct sockaddr *)addr, sizeof( struct sockaddr_s ) );
			if ( ret == SOCKET_ERROR ) {
				if ( WSAGetLastError() != WSAEWOULDBLOCK ) {
					return qfalse;
				}
				Sleep( 1000 );
			} //end if
			else
			{
				written += ret;
			}
		}
	} //end if
	else
	{
		written = 0;
		while ( written < len )
		{
			ret = send( socket, buf, len, 0 );
			if ( ret == SOCKET_ERROR ) {
				if ( WSAGetLastError() != WSAEWOULDBLOCK ) {
					return qfalse;
				}
				Sleep( 1000 );
			} //end if
			else
			{
				written += ret;
			}
		}
	} //end else
	if ( ret == SOCKET_ERROR ) {
		WinPrint( "WINS_Write: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
	} //end if
	return ( ret == len );
}