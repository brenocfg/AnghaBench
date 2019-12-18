#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drbd_state_change {unsigned int n_devices; unsigned int n_connections; TYPE_2__* connections; TYPE_1__* devices; TYPE_3__* resource; } ;
struct drbd_device {int /*<<< orphan*/  kref; } ;
struct drbd_connection {int /*<<< orphan*/  kref; } ;
struct TYPE_8__ {int /*<<< orphan*/  kref; } ;
struct TYPE_7__ {TYPE_4__* resource; } ;
struct TYPE_6__ {struct drbd_connection* connection; } ;
struct TYPE_5__ {struct drbd_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_destroy_connection ; 
 int /*<<< orphan*/  drbd_destroy_device ; 
 int /*<<< orphan*/  drbd_destroy_resource ; 
 int /*<<< orphan*/  kfree (struct drbd_state_change*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void forget_state_change(struct drbd_state_change *state_change)
{
	unsigned int n;

	if (!state_change)
		return;

	if (state_change->resource->resource)
		kref_put(&state_change->resource->resource->kref, drbd_destroy_resource);
	for (n = 0; n < state_change->n_devices; n++) {
		struct drbd_device *device = state_change->devices[n].device;

		if (device)
			kref_put(&device->kref, drbd_destroy_device);
	}
	for (n = 0; n < state_change->n_connections; n++) {
		struct drbd_connection *connection =
			state_change->connections[n].connection;

		if (connection)
			kref_put(&connection->kref, drbd_destroy_connection);
	}
	kfree(state_change);
}