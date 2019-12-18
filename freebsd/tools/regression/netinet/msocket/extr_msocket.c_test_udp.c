#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_3__ sin_addr; void* sin_port; void* sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {void* s_addr; } ;
struct TYPE_4__ {void* s_addr; } ;
struct ip_mreq {TYPE_2__ imr_interface; TYPE_1__ imr_multiaddr; } ;
struct in_addr {void* s_addr; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  message ;
typedef  int /*<<< orphan*/  if_addr ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_MULTICAST_IF ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 char* TEST_MADDR ; 
 int /*<<< orphan*/  UDP_PORT ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char,...) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 void* inet_addr (char*) ; 
 int recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in_addr*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_add_multi (int,char*,struct ip_mreq,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_drop_multi (int,char*,struct ip_mreq,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_udp(void)
{
	struct sockaddr_in sin;
	struct ip_mreq imr;
	struct in_addr if_addr;
	char message;
	ssize_t len;
	int sock;

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		err(-1, "FAIL: test_udp: socket(PF_INET, SOCK_DGRAM)");

	if (fcntl(sock, F_SETFL, O_NONBLOCK) < 0)
		err(-1, "FAIL: test_udp: fcntl(F_SETFL, O_NONBLOCK)");

	bzero(&sin, sizeof(sin));
	sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(UDP_PORT);
	sin.sin_addr.s_addr = inet_addr(TEST_MADDR);

	if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		err(-1, "FAIL: test_udp: bind(udp_sock, 127.0.0.1:%d",
		    UDP_PORT);

	/* Arbitrary. */
	imr.imr_multiaddr.s_addr = inet_addr(TEST_MADDR);

	/* Localhost should be OK. */
	imr.imr_interface.s_addr = inet_addr("127.0.0.1");

	/*
	 * Tell socket what interface to send on -- use localhost.
	 */
	if_addr.s_addr = inet_addr("127.0.0.1");
	if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, &if_addr,
	    sizeof(if_addr)) < 0)
		err(-1, "test_udp: setsockopt(IPPROTO_IP, IP_MULTICAST_IF)");

	test_add_multi(sock, "udp_sock", imr, 0);

	bzero(&sin, sizeof(sin));
	sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(UDP_PORT);
	sin.sin_addr.s_addr = inet_addr(TEST_MADDR);

	message = 'A';
	len = sizeof(message);
	len = sendto(sock, &message, len, 0, (struct sockaddr *)&sin,
	    sizeof(sin));
	if (len < 0)
		err(-1, "test_udp: sendto");

	if (len != sizeof(message))
		errx(-1, "test_udp: sendto: expected to send %d, instead %d",
		    sizeof(message), len);

	message = 'B';
	len = sizeof(sin);
	len = recvfrom(sock, &message, sizeof(message), 0,
	    (struct sockaddr *)&sin, &len);
	if (len < 0)
		err(-1, "test_udp: recvfrom");

	if (len != sizeof(message))
		errx(-1, "test_udp: recvfrom: len %d != message len %d",
		    len, sizeof(message));

	if (message != 'A')
		errx(-1, "test_udp: recvfrom: expected 'A', got '%c'",
		    message);

	test_drop_multi(sock, "udp_sock", imr, 0);

	close(sock);
}