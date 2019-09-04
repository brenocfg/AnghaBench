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
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int O_BINARY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ WSASocket (int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _open_osfhandle (scalar_t__,int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  ensure_socket_initialization () ; 
 int /*<<< orphan*/  errno ; 
 int error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int mingw_socket(int domain, int type, int protocol)
{
	int sockfd;
	SOCKET s;

	ensure_socket_initialization();
	s = WSASocket(domain, type, protocol, NULL, 0, 0);
	if (s == INVALID_SOCKET) {
		/*
		 * WSAGetLastError() values are regular BSD error codes
		 * biased by WSABASEERR.
		 * However, strerror() does not know about networking
		 * specific errors, which are values beginning at 38 or so.
		 * Therefore, we choose to leave the biased error code
		 * in errno so that _if_ someone looks up the code somewhere,
		 * then it is at least the number that are usually listed.
		 */
		errno = WSAGetLastError();
		return -1;
	}
	/* convert into a file descriptor */
	if ((sockfd = _open_osfhandle(s, O_RDWR|O_BINARY)) < 0) {
		closesocket(s);
		return error("unable to make a socket file descriptor: %s",
			strerror(errno));
	}
	return sockfd;
}