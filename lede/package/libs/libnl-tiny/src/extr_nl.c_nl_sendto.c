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
struct sockaddr {int dummy; } ;
struct nl_sock {int /*<<< orphan*/  s_peer; int /*<<< orphan*/  s_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int nl_syserr2nlerr (int /*<<< orphan*/ ) ; 
 int sendto (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

int nl_sendto(struct nl_sock *sk, void *buf, size_t size)
{
	int ret;

	ret = sendto(sk->s_fd, buf, size, 0, (struct sockaddr *)
		     &sk->s_peer, sizeof(sk->s_peer));
	if (ret < 0)
		return -nl_syserr2nlerr(errno);

	return ret;
}