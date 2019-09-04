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
 int /*<<< orphan*/  WINS_ErrorMessage (int) ; 
 int WSAECONNREFUSED ; 
 int WSAEWOULDBLOCK ; 
 int WSAGetLastError () ; 
 int /*<<< orphan*/  WinPrint (char*,int /*<<< orphan*/ ) ; 
 int recv (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int recvfrom (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 

int WINS_Read( int socket, byte *buf, int len, struct sockaddr_s *addr ){
	int addrlen = sizeof( struct sockaddr_s );
	int ret, errno;

	if ( addr ) {
		ret = recvfrom( socket, buf, len, 0, (struct sockaddr *)addr, &addrlen );
		if ( ret == -1 ) {
			errno = WSAGetLastError();

			if ( errno == WSAEWOULDBLOCK || errno == WSAECONNREFUSED ) {
				return 0;
			}
		} //end if
	} //end if
	else
	{
		ret = recv( socket, buf, len, 0 );
		if ( ret == SOCKET_ERROR ) {
			errno = WSAGetLastError();

			if ( errno == WSAEWOULDBLOCK || errno == WSAECONNREFUSED ) {
				return 0;
			}
		} //end if
	} //end else
	if ( ret == SOCKET_ERROR ) {
		WinPrint( "WINS_Read: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
	} //end if
	return ret;
}