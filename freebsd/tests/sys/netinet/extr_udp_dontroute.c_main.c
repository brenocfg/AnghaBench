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
typedef  int uint16_t ;
struct sockaddr_storage {int ss_len; void* ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; void* sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; void* sin_port; } ;
struct sockaddr {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  dst ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_DONTROUTE ; 
 int /*<<< orphan*/  bzero (struct sockaddr_storage*,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 void* htons (int const) ; 
 int inet_pton (void*,char const*,int /*<<< orphan*/ *) ; 
 int open (char const*,int) ; 
 scalar_t__ read (int,char*,size_t const) ; 
 int sendto (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
main(int argc, char **argv)
{
	struct sockaddr_storage dst;
	int s, t;
	int opt;
	int ret;
	ssize_t len;
	const char* sendbuf = "Hello, World!";
	const size_t buflen = 80;
	char recvbuf[buflen];
	bool v6 = false;
	const char *addr, *tapdev;
	const uint16_t port = 46120;

	bzero(&dst, sizeof(dst));
	if (argc < 3 || argc > 4) {
		fprintf(stderr, "Usage: %s [-6] ip_address tapdev\n", argv[0]);
		exit(2);
	}

	if (strcmp("-6", argv[1]) == 0) {
		v6 = true;
		addr = argv[2];
		tapdev = argv[3];
	} else {
		addr = argv[1];
		tapdev = argv[2];
	}

	t = open(tapdev, O_RDWR | O_NONBLOCK);
	if (t < 0)
		err(EXIT_FAILURE, "open");

	if (v6)
		s = socket(PF_INET6, SOCK_DGRAM, 0);
	else
		s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s < 0)
		err(EXIT_FAILURE, "socket");
	opt = 1;

	ret = setsockopt(s, SOL_SOCKET, SO_DONTROUTE, &opt, sizeof(opt));
	if (ret == -1)
		err(EXIT_FAILURE, "setsockopt(SO_DONTROUTE)");

	if (v6) {
		struct sockaddr_in6 *dst6 = ((struct sockaddr_in6*)&dst);

		dst.ss_len = sizeof(struct sockaddr_in6);
		dst.ss_family = AF_INET6;
		dst6->sin6_port = htons(port);
		ret = inet_pton(AF_INET6, addr, &dst6->sin6_addr);
	} else {
		struct sockaddr_in *dst4 = ((struct sockaddr_in*)&dst);

		dst.ss_len = sizeof(struct sockaddr_in);
		dst.ss_family = AF_INET;
		dst4->sin_port = htons(port);
		ret = inet_pton(AF_INET, addr, &dst4->sin_addr);
	}
	if (ret != 1)
		err(EXIT_FAILURE, "inet_pton returned %d", ret);

	ret = sendto(s, sendbuf, strlen(sendbuf), 0, (struct sockaddr*)&dst,
	    dst.ss_len);
	if (ret == -1)
		err(EXIT_FAILURE, "sendto");

	/* Verify that the packet went to the desired tap device */

	len = read(t, recvbuf, buflen);
	if (len == 0)
		errx(EXIT_FAILURE, "read returned EOF");
	else if (len < 0 && errno == EAGAIN)
		errx(EXIT_FAILURE, "Did not receive any packets");
	else if (len < 0)
		err(EXIT_FAILURE, "read");

	/*
	 * If read returned anything at all, consider it a success.  The packet
	 * should be an Ethernet frame containing an ARP request for
	 * ip_address.  We won't bother to decode it
	 */
	return (0);
}