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
struct nl_sock {int s_fd; scalar_t__ s_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 

void nl_close(struct nl_sock *sk)
{
	if (sk->s_fd >= 0) {
		close(sk->s_fd);
		sk->s_fd = -1;
	}

	sk->s_proto = 0;
}