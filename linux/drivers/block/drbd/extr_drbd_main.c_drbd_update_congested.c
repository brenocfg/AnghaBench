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
struct sock {int sk_wmem_queued; int sk_sndbuf; } ;
struct TYPE_4__ {TYPE_1__* socket; } ;
struct drbd_connection {int /*<<< orphan*/  flags; TYPE_2__ data; } ;
struct TYPE_3__ {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_CONGESTED ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drbd_update_congested(struct drbd_connection *connection)
{
	struct sock *sk = connection->data.socket->sk;
	if (sk->sk_wmem_queued > sk->sk_sndbuf * 4 / 5)
		set_bit(NET_CONGESTED, &connection->flags);
}