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
struct drbd_state_change {int n_connections; int n_devices; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int notifications_for_state_change(struct drbd_state_change *state_change)
{
	return 1 +
	       state_change->n_connections +
	       state_change->n_devices +
	       state_change->n_devices * state_change->n_connections;
}