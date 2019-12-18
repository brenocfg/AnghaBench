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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 scalar_t__ WSAEINPROGRESS ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int connect (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_err_addr (char*,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ tcp_connect_errno_needs_log (struct sockaddr*,int /*<<< orphan*/ ) ; 

int
outnet_tcp_connect(int s, struct sockaddr_storage* addr, socklen_t addrlen)
{
	if(connect(s, (struct sockaddr*)addr, addrlen) == -1) {
#ifndef USE_WINSOCK
#ifdef EINPROGRESS
		if(errno != EINPROGRESS) {
#endif
			if(tcp_connect_errno_needs_log(
				(struct sockaddr*)addr, addrlen))
				log_err_addr("outgoing tcp: connect",
					strerror(errno), addr, addrlen);
			close(s);
			return 0;
#ifdef EINPROGRESS
		}
#endif
#else /* USE_WINSOCK */
		if(WSAGetLastError() != WSAEINPROGRESS &&
			WSAGetLastError() != WSAEWOULDBLOCK) {
			closesocket(s);
			return 0;
		}
#endif
	}
	return 1;
}