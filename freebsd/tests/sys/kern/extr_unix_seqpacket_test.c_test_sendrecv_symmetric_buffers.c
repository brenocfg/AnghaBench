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
typedef  int /*<<< orphan*/  bufsize ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK_EQ_MSG (int const,int,char*,int const,int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MSG_EOR ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  bzero (char*,int const) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  do_socketpair (int*) ; 
 int /*<<< orphan*/  do_socketpair_nonblocking (int*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int recv (int,char*,int const,int /*<<< orphan*/ ) ; 
 int send (int,char*,int const,int /*<<< orphan*/ ) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
test_sendrecv_symmetric_buffers(int bufsize, int blocking) {
	int s;
	int sv[2];
	const ssize_t pktsize = bufsize / 2;
	char sndbuf[pktsize];
	char recv_buf[pktsize];
	ssize_t ssize, rsize;

	/* setup the socket pair */
	if (blocking)
		do_socketpair(sv);
	else
		do_socketpair_nonblocking(sv);

	/* Setup the buffers */
	s = setsockopt(sv[0], SOL_SOCKET, SO_SNDBUF, &bufsize, sizeof(bufsize));
	ATF_REQUIRE_EQ(0, s);
	s = setsockopt(sv[1], SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof(bufsize));
	ATF_REQUIRE_EQ(0, s);

	/* Fill the send buffer */
	bzero(sndbuf, pktsize);

	/* send and receive the packet */
	ssize = send(sv[0], sndbuf, pktsize, MSG_EOR);
	if (ssize < 0) {
		perror("send");
		atf_tc_fail("send returned < 0");
	}
	ATF_CHECK_EQ_MSG(pktsize, ssize, "expected %zd=send(...) but got %zd",
	    pktsize, ssize);

	rsize = recv(sv[1], recv_buf, pktsize, MSG_WAITALL);
	if (rsize < 0) {
		perror("recv");
		atf_tc_fail("recv returned < 0");
	}
	ATF_CHECK_EQ_MSG(pktsize, rsize, "expected %zd=send(...) but got %zd",
	    pktsize, rsize);
	close(sv[0]);
	close(sv[1]);
}