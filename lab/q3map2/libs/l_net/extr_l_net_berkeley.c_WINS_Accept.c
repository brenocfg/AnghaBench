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
typedef  int qboolean ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  WINS_ErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  WinPrint (char*,...) ; 
 int accept (int,struct sockaddr*,int*) ; 
 scalar_t__ errno ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

int WINS_Accept( int socket, struct sockaddr_s *addr ){
	socklen_t addrlen = sizeof( struct sockaddr_s );
	int newsocket;
	qboolean _true = 1;

	newsocket = accept( socket, (struct sockaddr *)addr, &addrlen );
	if ( newsocket == INVALID_SOCKET ) {
		if ( errno == EAGAIN ) {
			return -1;
		}
		WinPrint( "WINS_Accept: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		return -1;
	} //end if
	  //
	if ( setsockopt( newsocket, IPPROTO_TCP, TCP_NODELAY, (void *) &_true, sizeof( int ) ) == SOCKET_ERROR ) {
		WinPrint( "WINS_Accept: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		WinPrint( "setsockopt error\n" );
	} //end if
	return newsocket;
}