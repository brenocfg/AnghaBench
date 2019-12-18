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
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
do_socketpair_nonblocking(int *sv)
{
	int s;

	s = socketpair(PF_LOCAL, SOCK_SEQPACKET, 0, sv);
	ATF_REQUIRE_EQ(0, s);
	ATF_REQUIRE(sv[0] >= 0);
	ATF_REQUIRE(sv[1] >= 0);
	ATF_REQUIRE(sv[0] != sv[1]);
	ATF_REQUIRE(-1 != fcntl(sv[0], F_SETFL, O_NONBLOCK));
	ATF_REQUIRE(-1 != fcntl(sv[1], F_SETFL, O_NONBLOCK));
}