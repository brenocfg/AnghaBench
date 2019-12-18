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
struct icmp6_filter {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  ic6f ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP6_FILTER ; 
 int /*<<< orphan*/  ICMP6_FILTER_SETBLOCKALL (struct icmp6_filter*) ; 
 int /*<<< orphan*/  ICMP6_FILTER_SETPASSALL (struct icmp6_filter*) ; 
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct icmp6_filter*,int*) ; 
 struct icmp6_filter ic6f_blockall ; 
 struct icmp6_filter ic6f_passall ; 
 scalar_t__ memcmp (struct icmp6_filter*,struct icmp6_filter*,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct icmp6_filter*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	struct icmp6_filter ic6f;
	socklen_t len;
	int s;

	ICMP6_FILTER_SETPASSALL(&ic6f_passall);
	ICMP6_FILTER_SETBLOCKALL(&ic6f_blockall);

	s = socket(PF_INET6, SOCK_RAW, 0);
	if (s < 0)
		err(-1, "socket(PF_INET6, SOCK_RAW, 0)");

	/*
	 * Confirm that we can read before the first set, and that the
	 * default is to pass all ICMP.
	 */
	len = sizeof(ic6f);
	if (getsockopt(s, IPPROTO_ICMPV6, ICMP6_FILTER, &ic6f, &len) < 0)
		err(-1, "1: getsockopt(ICMP6_FILTER)");
	if (memcmp(&ic6f, &ic6f_passall, sizeof(ic6f)) != 0)
		errx(-1, "1: getsockopt(ICMP6_FILTER) - default not passall");

	/*
	 * Confirm that we can write a pass all filter to the socket.
	 */
	len = sizeof(ic6f);
	ICMP6_FILTER_SETPASSALL(&ic6f);
	if (setsockopt(s, IPPROTO_ICMPV6, ICMP6_FILTER, &ic6f, len) < 0)
		err(-1, "2: setsockopt(ICMP6_FILTER, PASSALL)");

	/*
	 * Confirm that we can still read a pass all filter.
	 */
	len = sizeof(ic6f);
	if (getsockopt(s, IPPROTO_ICMPV6, ICMP6_FILTER, &ic6f, &len) < 0)
		err(-1, "3: getsockopt(ICMP6_FILTER)");
	if (memcmp(&ic6f, &ic6f_passall, sizeof(ic6f)) != 0)
		errx(-1, "3: getsockopt(ICMP6_FILTER) - not passall");

	/*
	 * Confirm that we can write a block all filter to the socket.
	 */
	len = sizeof(ic6f);
	ICMP6_FILTER_SETBLOCKALL(&ic6f);
	if (setsockopt(s, IPPROTO_ICMPV6, ICMP6_FILTER, &ic6f, len) < 0)
		err(-1, "4: setsockopt(ICMP6_FILTER, BLOCKALL)");

	/*
	 * Confirm that we can read back a block all filter.
	 */
	len = sizeof(ic6f);
	if (getsockopt(s, IPPROTO_ICMPV6, ICMP6_FILTER, &ic6f, &len) < 0)
		err(-1, "5: getsockopt(ICMP6_FILTER)");
	if (memcmp(&ic6f, &ic6f_blockall, sizeof(ic6f)) != 0)
		errx(-1, "5: getsockopt(ICMP6_FILTER) - not blockall");

	/*
	 * For completeness, confirm that we can reset to the default.
	 */
	len = sizeof(ic6f);
	ICMP6_FILTER_SETPASSALL(&ic6f);
	if (setsockopt(s, IPPROTO_ICMPV6, ICMP6_FILTER, &ic6f, len) < 0)
		err(-1, "6: setsockopt(ICMP6_FILTER, PASSALL)");

	/*
	 * ... And that we can read back the pass all rule again.
	 */
	len = sizeof(ic6f);
	if (getsockopt(s, IPPROTO_ICMPV6, ICMP6_FILTER, &ic6f, &len) < 0)
		err(-1, "7: getsockopt(ICMP6_FILTER)");
	if (memcmp(&ic6f, &ic6f_passall, sizeof(ic6f)) != 0)
		errx(-1, "7: getsockopt(ICMP6_FILTER) - not passall");

	close(s);
	return (0);
}