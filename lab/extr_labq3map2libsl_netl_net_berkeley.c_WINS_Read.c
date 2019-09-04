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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ ENOTCONN ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  WINS_ErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  WinPrint (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int recv (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int recvfrom (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 

int WINS_Read( int socket, byte *buf, int len, struct sockaddr_s *addr ){
	socklen_t addrlen = sizeof( struct sockaddr_s );
	int ret;

	if ( addr ) {
		ret = recvfrom( socket, buf, len, 0, (struct sockaddr *)addr, &addrlen );
		if ( ret == -1 ) {
//			errno = WSAGetLastError();

			if ( errno == EAGAIN || errno == ENOTCONN ) {
				return 0;
			}
		} //end if
	} //end if
	else
	{
		ret = recv( socket, buf, len, 0 );
		// if there's no data on the socket ret == -1 and errno == EAGAIN
		// MSDN states that if ret == 0 the socket has been closed
		// man recv doesn't say anything
		if ( ret == 0 ) {
			return -1;
		}
		if ( ret == SOCKET_ERROR ) {
//			errno = WSAGetLastError();

			if ( errno == EAGAIN || errno == ENOTCONN ) {
				return 0;
			}
		} //end if
	} //end else
	if ( ret == SOCKET_ERROR ) {
		WinPrint( "WINS_Read: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
	} //end if
	return ret;
}