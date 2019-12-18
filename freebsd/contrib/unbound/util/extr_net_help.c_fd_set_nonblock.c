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
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ioctlsocket (int,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsa_strerror (int /*<<< orphan*/ ) ; 

int 
fd_set_nonblock(int s) 
{
#ifdef HAVE_FCNTL
	int flag;
	if((flag = fcntl(s, F_GETFL)) == -1) {
		log_err("can't fcntl F_GETFL: %s", strerror(errno));
		flag = 0;
	}
	flag |= O_NONBLOCK;
	if(fcntl(s, F_SETFL, flag) == -1) {
		log_err("can't fcntl F_SETFL: %s", strerror(errno));
		return 0;
	}
#elif defined(HAVE_IOCTLSOCKET)
	unsigned long on = 1;
	if(ioctlsocket(s, FIONBIO, &on) != 0) {
		log_err("can't ioctlsocket FIONBIO on: %s", 
			wsa_strerror(WSAGetLastError()));
	}
#endif
	return 1;
}