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
struct drbd_peer_device {int /*<<< orphan*/  device; } ;
struct drbd_connection {int /*<<< orphan*/  peer_devices; } ;

/* Variables and functions */
 int device_to_minor (int /*<<< orphan*/ ) ; 
 struct drbd_peer_device* idr_get_next (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int conn_lowest_minor(struct drbd_connection *connection)
{
	struct drbd_peer_device *peer_device;
	int vnr = 0, minor = -1;

	rcu_read_lock();
	peer_device = idr_get_next(&connection->peer_devices, &vnr);
	if (peer_device)
		minor = device_to_minor(peer_device->device);
	rcu_read_unlock();

	return minor;
}