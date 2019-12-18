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
 scalar_t__ EPROTOTYPE ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int
main(void)
{
	int sock, socks[2];

	sock = socket(PF_LOCAL, SOCK_STREAM, 0);
	if (sock < 0)
		err(-1, "socket(PF_LOCAL, SOCK_STREAM, 0)");
	close(sock);

	sock = socket(PF_LOCAL, SOCK_DGRAM, 0);
	if (sock < 0)
		err(-1, "socket(PF_LOCAL, SOCK_DGRAM, 0)");
	close(sock);

	sock = socket(PF_LOCAL, SOCK_RAW, 0);
	if (sock >= 0) {
		close(sock);
		errx(-1, "socket(PF_LOCAL, SOCK_RAW, 0) returned %d", sock);
	}
	if (errno != EPROTOTYPE)
		err(-1, "socket(PF_LOCAL, SOCK_RAW, 0)");

	if (socketpair(PF_LOCAL, SOCK_STREAM, 0, socks) < 0)
		err(-1, "socketpair(PF_LOCAL, SOCK_STREAM, 0, socks)");
	if (socks[0] < 0)
		errx(-1, "socketpair(PF_LOCAL, SOCK_STREAM, 0, socks) [0] < 0");
	if (socks[1] < 0)
		errx(-1, "socketpair(PF_LOCAL, SOCK_STREAM, 0, socks) [1] < 1");
	close(socks[0]);
	close(socks[1]);

	if (socketpair(PF_LOCAL, SOCK_DGRAM, 0, socks) < 0)
		err(-1, "socketpair(PF_LOCAL, SOCK_DGRAM, 0, socks)");
	if (socks[0] < 0)
		errx(-1, "socketpair(PF_LOCAL, SOCK_DGRAM, 0, socks) [0] < 0");
	if (socks[1] < 0)
		errx(-1, "socketpair(PF_LOCAL, SOCK_DGRAM, 0, socks) [1] < 1");
	close(socks[0]);
	close(socks[1]);

	return (0);
}