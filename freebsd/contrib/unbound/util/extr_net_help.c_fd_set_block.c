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

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 scalar_t__ WSAEINVAL ; 
 scalar_t__ WSAGetLastError () ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ioctlsocket (int,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int verbosity ; 
 int /*<<< orphan*/  wsa_strerror (scalar_t__) ; 

int 
fd_set_block(int s) 
{
#ifdef HAVE_FCNTL
	int flag;
	if((flag = fcntl(s, F_GETFL)) == -1) {
		log_err("cannot fcntl F_GETFL: %s", strerror(errno));
		flag = 0;
	}
	flag &= ~O_NONBLOCK;
	if(fcntl(s, F_SETFL, flag) == -1) {
		log_err("cannot fcntl F_SETFL: %s", strerror(errno));
		return 0;
	}
#elif defined(HAVE_IOCTLSOCKET)
	unsigned long off = 0;
	if(ioctlsocket(s, FIONBIO, &off) != 0) {
		if(WSAGetLastError() != WSAEINVAL || verbosity >= 4)
			log_err("can't ioctlsocket FIONBIO off: %s", 
				wsa_strerror(WSAGetLastError()));
	}
#endif	
	return 1;
}