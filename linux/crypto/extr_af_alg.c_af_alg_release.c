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
struct socket {int /*<<< orphan*/ * sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ *) ; 

int af_alg_release(struct socket *sock)
{
	if (sock->sk) {
		sock_put(sock->sk);
		sock->sk = NULL;
	}
	return 0;
}