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
struct net_conf {int max_buffers; } ;
struct drbd_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* connection; } ;
struct TYPE_3__ {int /*<<< orphan*/  net_conf; } ;

/* Variables and functions */
 TYPE_2__* first_peer_device (struct drbd_device*) ; 
 struct net_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline int drbd_get_max_buffers(struct drbd_device *device)
{
	struct net_conf *nc;
	int mxb;

	rcu_read_lock();
	nc = rcu_dereference(first_peer_device(device)->connection->net_conf);
	mxb = nc ? nc->max_buffers : 1000000;  /* arbitrary limit on open requests */
	rcu_read_unlock();

	return mxb;
}