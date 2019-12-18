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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct pollfd {int fd; scalar_t__ revents; int /*<<< orphan*/  events; } ;
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  fd_mask ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFDBITS ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  rcvsock ; 
 int recvmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 scalar_t__ select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int waittime ; 

int
wait_for_reply(int sock, struct msghdr *mhdr)
{
#ifdef HAVE_POLL
	struct pollfd pfd[1];
	int cc = 0;

	pfd[0].fd = sock;
	pfd[0].events = POLLIN;
	pfd[0].revents = 0;

	if (poll(pfd, 1, waittime * 1000) > 0)
		cc = recvmsg(rcvsock, mhdr, 0);

	return (cc);
#else
	fd_set *fdsp;
	struct timeval wait;
	int cc = 0, fdsn;

	fdsn = howmany(sock + 1, NFDBITS) * sizeof(fd_mask);
	if ((fdsp = (fd_set *)malloc(fdsn)) == NULL)
		err(1, "malloc");
	memset(fdsp, 0, fdsn);
	FD_SET(sock, fdsp);
	wait.tv_sec = waittime; wait.tv_usec = 0;

	if (select(sock+1, fdsp, (fd_set *)0, (fd_set *)0, &wait) > 0)
		cc = recvmsg(rcvsock, mhdr, 0);

	free(fdsp);
	return (cc);
#endif
}