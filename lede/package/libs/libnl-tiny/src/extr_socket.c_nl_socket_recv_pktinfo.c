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
struct nl_sock {int s_fd; } ;
typedef  int /*<<< orphan*/  state ;

/* Variables and functions */
 int /*<<< orphan*/  NETLINK_PKTINFO ; 
 int NLE_BAD_SOCK ; 
 int /*<<< orphan*/  SOL_NETLINK ; 
 int /*<<< orphan*/  errno ; 
 int nl_syserr2nlerr (int /*<<< orphan*/ ) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int nl_socket_recv_pktinfo(struct nl_sock *sk, int state)
{
	int err;

	if (sk->s_fd == -1)
		return -NLE_BAD_SOCK;

	err = setsockopt(sk->s_fd, SOL_NETLINK, NETLINK_PKTINFO,
			 &state, sizeof(state));
	if (err < 0)
		return -nl_syserr2nlerr(errno);

	return 0;
}