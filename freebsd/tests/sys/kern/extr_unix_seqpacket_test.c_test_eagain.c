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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sndbufsize ;
typedef  int /*<<< orphan*/  rcvbufsize ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EAGAIN ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  MSG_EOR ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_pass () ; 
 int /*<<< orphan*/  bzero (char*,size_t const) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  do_socketpair_nonblocking (int*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  perror (char*) ; 
 int send (int,char*,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
test_eagain(int sndbufsize, int rcvbufsize)
{
	int i;
	int sv[2];
	const size_t totalsize = (sndbufsize + rcvbufsize) * 2;
	const size_t pktsize = MIN(sndbufsize, rcvbufsize) / 4;
	const int numpkts = totalsize / pktsize;
	char sndbuf[pktsize];
	ssize_t ssize;

	/* setup the socket pair */
	do_socketpair_nonblocking(sv);
	/* Setup the buffers */
	ATF_REQUIRE_EQ(0, setsockopt(sv[0], SOL_SOCKET, SO_SNDBUF, &sndbufsize,
	    sizeof(sndbufsize)));
	ATF_REQUIRE_EQ(0, setsockopt(sv[1], SOL_SOCKET, SO_RCVBUF, &rcvbufsize,
	    sizeof(rcvbufsize)));

	bzero(sndbuf, pktsize);
	/* Send data until we get EAGAIN */
	for(i=0; i < numpkts; i++) {
		ssize = send(sv[0], sndbuf, pktsize, MSG_EOR);
		if (ssize == -1) {
			if (errno == EAGAIN) {
				close(sv[0]);
				close(sv[1]);
				atf_tc_pass();
			}
			else {
				perror("send");
				atf_tc_fail("send returned < 0 but not EAGAIN");
			}
		}
	}
	atf_tc_fail("Never got EAGAIN");
}