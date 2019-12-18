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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  optlen ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  TCP_KEEPIDLE ; 
 int keepalive ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rs_getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ rs_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void set_keepalive(int fd)
{
	int optval;
	socklen_t optlen = sizeof(optlen);

	optval = 1;
	if (rs_setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen)) {
		perror("rsetsockopt SO_KEEPALIVE");
		return;
	}

	optval = keepalive;
	if (rs_setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &optval, optlen))
		perror("rsetsockopt TCP_KEEPIDLE");

	if (!(rs_getsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen)))
		printf("Keepalive: %s\n", (optval ? "ON" : "OFF"));

	if (!(rs_getsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &optval, &optlen)))
		printf("  time: %i\n", optval);
}