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
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ geteuid () ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_addr (int,int,int) ; 
 int /*<<< orphan*/  test_if (int,int,int) ; 
 int /*<<< orphan*/  test_loop (int,int,int) ; 
 int /*<<< orphan*/  test_ttl (int,int,int) ; 
 int /*<<< orphan*/  test_udp () ; 

int
main(int argc, char *argv[])
{
	int raw_sock, tcp_sock, udp_sock;

	if (geteuid() != 0)
		errx(-1, "FAIL: root privilege required");

	raw_sock = socket(PF_INET, SOCK_RAW, 0);
	if (raw_sock == -1)
		err(-1, "FAIL: socket(PF_INET, SOCK_RAW)");

	tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (raw_sock == -1)
		err(-1, "FAIL: socket(PF_INET, SOCK_STREAM)");

	udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (raw_sock == -1)
		err(-1, "FAIL: socket(PF_INET, SOCK_DGRAM)");

	test_ttl(raw_sock, tcp_sock, udp_sock);
	test_loop(raw_sock, tcp_sock, udp_sock);
	test_if(raw_sock, tcp_sock, udp_sock);
	test_addr(raw_sock, tcp_sock, udp_sock);

	close(udp_sock);
	close(tcp_sock);
	close(raw_sock);

	test_udp();

	return (0);
}