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
typedef  int /*<<< orphan*/  nbuff ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int BUFFERLEN ; 
#define  EINTR 130 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
#define  R_IO_ERROR 129 
#define  R_MORE 128 
 int STRERROR (int) ; 
 int /*<<< orphan*/  debug (int,char*,int,...) ; 
 int do_kbuff (int,char*,int*) ; 
 int do_packet (int,char*) ; 
 int errno ; 
 int lfd ; 
 int nfd ; 
 int read (int,char*,int) ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  terminate ; 

void
do_io()
{
	char nbuff[BUFFERLEN];
	char buff[BUFFERLEN];
	fd_set mrd, rd;
	int maxfd;
	int inbuf;
	int n1;
	int left;

	FD_ZERO(&mrd);
	FD_SET(lfd, &mrd);
	FD_SET(nfd, &mrd);
	maxfd = nfd;
	if (lfd > maxfd)
		maxfd = lfd;
	debug(2, "nfd %d lfd %d maxfd %d\n", nfd, lfd, maxfd);

	inbuf = 0;
	/*
	 * A threaded approach to this loop would have one thread
	 * work on reading lfd (only) all the time and another thread
	 * working on reading nfd all the time.
	 */
	while (!terminate) {
		int n;

		rd = mrd;

		n = select(maxfd + 1, &rd, NULL, NULL, NULL);
		if (n < 0) {
			switch (errno)
			{
			case EINTR :
				continue;
			default :
				syslog(LOG_ERR, "select error: %m");
				debug(1, "select error: %s\n", STRERROR(errno));
				return;
			}
		}

		if (FD_ISSET(lfd, &rd)) {
			n1 = read(lfd, buff+inbuf, BUFFERLEN-inbuf);

			debug(3, "read(K):%d\n", n1);

			if (n1 <= 0) {
				syslog(LOG_ERR, "read error (k-header): %m");
				debug(1, "read error (k-header): %s\n",
				      STRERROR(errno));
				return;
			}

			left = 0;

			switch (do_kbuff(n1, buff, &left))
			{
			case R_IO_ERROR :
				return;
			case R_MORE :
				inbuf += left;
				break;
			default :
				inbuf = 0;
				break;
			}
		}

		if (FD_ISSET(nfd, &rd)) {
			n1 = recv(nfd, nbuff, sizeof(nbuff), 0);

			debug(3, "read(N):%d\n", n1);

			if (n1 <= 0) {
				syslog(LOG_ERR, "read error (n-header): %m");
				debug(1, "read error (n-header): %s\n",
				      STRERROR(errno));
				return;
			}

			switch (do_packet(n1, nbuff))
			{
			case R_IO_ERROR :
				return;
			default :
				break;
			}
		}
	}
}