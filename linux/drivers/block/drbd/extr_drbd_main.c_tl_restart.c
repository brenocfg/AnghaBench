#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drbd_connection {TYPE_1__* resource; } ;
typedef  enum drbd_req_event { ____Placeholder_drbd_req_event } drbd_req_event ;
struct TYPE_2__ {int /*<<< orphan*/  req_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _tl_restart (struct drbd_connection*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void tl_restart(struct drbd_connection *connection, enum drbd_req_event what)
{
	spin_lock_irq(&connection->resource->req_lock);
	_tl_restart(connection, what);
	spin_unlock_irq(&connection->resource->req_lock);
}