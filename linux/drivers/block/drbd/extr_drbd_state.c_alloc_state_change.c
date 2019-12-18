#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drbd_state_change {unsigned int n_devices; unsigned int n_connections; TYPE_3__* connections; TYPE_2__* devices; TYPE_1__* resource; void* peer_devices; } ;
struct drbd_peer_device_state_change {int dummy; } ;
struct drbd_device_state_change {int dummy; } ;
struct drbd_connection_state_change {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {int /*<<< orphan*/ * connection; } ;
struct TYPE_5__ {int /*<<< orphan*/ * device; } ;
struct TYPE_4__ {int /*<<< orphan*/ * resource; } ;

/* Variables and functions */
 struct drbd_state_change* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drbd_state_change *alloc_state_change(unsigned int n_devices, unsigned int n_connections, gfp_t gfp)
{
	struct drbd_state_change *state_change;
	unsigned int size, n;

	size = sizeof(struct drbd_state_change) +
	       n_devices * sizeof(struct drbd_device_state_change) +
	       n_connections * sizeof(struct drbd_connection_state_change) +
	       n_devices * n_connections * sizeof(struct drbd_peer_device_state_change);
	state_change = kmalloc(size, gfp);
	if (!state_change)
		return NULL;
	state_change->n_devices = n_devices;
	state_change->n_connections = n_connections;
	state_change->devices = (void *)(state_change + 1);
	state_change->connections = (void *)&state_change->devices[n_devices];
	state_change->peer_devices = (void *)&state_change->connections[n_connections];
	state_change->resource->resource = NULL;
	for (n = 0; n < n_devices; n++)
		state_change->devices[n].device = NULL;
	for (n = 0; n < n_connections; n++)
		state_change->connections[n].connection = NULL;
	return state_change;
}