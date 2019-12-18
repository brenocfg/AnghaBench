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
struct evdev_client {int ec_revoked; int /*<<< orphan*/  ec_evdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVDEV_LOCK_ASSERT (int /*<<< orphan*/ ) ; 

void
evdev_revoke_client(struct evdev_client *client)
{

	EVDEV_LOCK_ASSERT(client->ec_evdev);

	client->ec_revoked = true;
}