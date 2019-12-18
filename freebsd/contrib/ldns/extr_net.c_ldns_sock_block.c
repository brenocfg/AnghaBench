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
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ioctlsocket (int,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void
ldns_sock_block(int sockfd)
{
#ifdef HAVE_FCNTL
	int flag;
	if((flag = fcntl(sockfd, F_GETFL)) != -1) {
		flag &= ~O_NONBLOCK;
		if(fcntl(sockfd, F_SETFL, flag) == -1) {
			/* ignore error, continue */
		}
	}
#elif defined(HAVE_IOCTLSOCKET)
	unsigned long off = 0;
	if(ioctlsocket(sockfd, FIONBIO, &off) != 0) {
		/* ignore error, continue */
	}
#endif
}