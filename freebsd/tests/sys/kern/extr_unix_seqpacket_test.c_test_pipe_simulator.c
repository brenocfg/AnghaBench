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
 int /*<<< orphan*/  ATF_CHECK_EQ_MSG (int const,int,char*,...) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EMSGSIZE ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  MSG_EOR ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  do_socketpair_nonblocking (int*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcmp (char*,char*,int const) ; 
 int /*<<< orphan*/  memset (char*,int,int const) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int recv (int,char*,int const,int /*<<< orphan*/ ) ; 
 int send (int,char*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
test_pipe_simulator(int sndbufsize, int rcvbufsize)
{
	int num_sent, num_received;
	int sv[2];
	const ssize_t pktsize = MIN(sndbufsize, rcvbufsize) / 4;
	int numpkts;
	char sndbuf[pktsize];
	char rcvbuf[pktsize];
	char comparebuf[pktsize];
	ssize_t ssize, rsize;
	bool currently_sending = true;

	/* setup the socket pair */
	do_socketpair_nonblocking(sv);
	/* Setup the buffers */
	ATF_REQUIRE_EQ(0, setsockopt(sv[0], SOL_SOCKET, SO_SNDBUF, &sndbufsize,
	    sizeof(sndbufsize)));
	ATF_REQUIRE_EQ(0, setsockopt(sv[1], SOL_SOCKET, SO_RCVBUF, &rcvbufsize,
	    sizeof(rcvbufsize)));

	/* Send a total amount of data comfortably greater than the buffers */
	numpkts = MAX(sndbufsize, rcvbufsize) * 8 / pktsize;
	for (num_sent=0, num_received=0;
	     num_sent < numpkts || num_received < numpkts; ) {
		if (currently_sending && num_sent < numpkts) {
			/* The simulated sending process */
			/* fill the buffer */
			memset(sndbuf, num_sent, pktsize);
			ssize = send(sv[0], sndbuf, pktsize, MSG_EOR);
			if (ssize < 0) {
				/*
				 * XXX: This is bug-compatible with the kernel.
				 * The kernel returns EMSGSIZE when it should
				 * return EAGAIN
				 */
				if (errno == EAGAIN || errno == EMSGSIZE)
					currently_sending = false;
				else {
					perror("send");
					atf_tc_fail("send failed");
				}
			} else  {
				ATF_CHECK_EQ_MSG(pktsize, ssize,
				    "expected %zd=send(...) but got %zd",
				    pktsize, ssize);
				num_sent++;
			}
		} else {
			/* The simulated receiving process */
			rsize = recv(sv[1], rcvbuf, pktsize, MSG_WAITALL);
			if (rsize < 0) {
				if (errno == EAGAIN) {
					currently_sending = true;
					ATF_REQUIRE_MSG(num_sent < numpkts,
					    "Packets were lost!");
				}
				else {
					perror("recv");
					atf_tc_fail("recv failed");
				}
			} else  {
				ATF_CHECK_EQ_MSG(pktsize, rsize,
				    "expected %zd=recv(...) but got %zd",
				    pktsize, rsize);
				memset(comparebuf, num_received, pktsize);
				ATF_CHECK_EQ_MSG(0, memcmp(comparebuf, rcvbuf,
				    			   pktsize),
				    "Received data miscompare");
				num_received++;
			}
		}
	}
	close(sv[0]);
	close(sv[1]);
}