#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nl_pid; void* nl_family; } ;
struct TYPE_3__ {void* nl_family; } ;
struct nl_sock {int s_fd; TYPE_2__ s_local; int /*<<< orphan*/  s_seq_next; int /*<<< orphan*/  s_seq_expect; TYPE_1__ s_peer; struct nl_cb* s_cb; } ;
struct nl_cb {int dummy; } ;

/* Variables and functions */
 void* AF_NETLINK ; 
 scalar_t__ UINT_MAX ; 
 struct nl_sock* calloc (int,int) ; 
 scalar_t__ generate_local_port () ; 
 int /*<<< orphan*/  nl_socket_free (struct nl_sock*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nl_sock *__alloc_socket(struct nl_cb *cb)
{
	struct nl_sock *sk;

	sk = calloc(1, sizeof(*sk));
	if (!sk)
		return NULL;

	sk->s_fd = -1;
	sk->s_cb = cb;
	sk->s_local.nl_family = AF_NETLINK;
	sk->s_peer.nl_family = AF_NETLINK;
	sk->s_seq_expect = sk->s_seq_next = time(0);
	sk->s_local.nl_pid = generate_local_port();
	if (sk->s_local.nl_pid == UINT_MAX) {
		nl_socket_free(sk);
		return NULL;
	}

	return sk;
}