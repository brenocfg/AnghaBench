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
typedef  union drbd_state {int dummy; } drbd_state ;
struct drbd_connection {TYPE_1__* resource; } ;
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;
typedef  enum chg_state_flags { ____Placeholder_chg_state_flags } chg_state_flags ;
struct TYPE_2__ {int /*<<< orphan*/  req_lock; } ;

/* Variables and functions */
 int _conn_request_state (struct drbd_connection*,union drbd_state,union drbd_state,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

enum drbd_state_rv
conn_request_state(struct drbd_connection *connection, union drbd_state mask, union drbd_state val,
		   enum chg_state_flags flags)
{
	enum drbd_state_rv rv;

	spin_lock_irq(&connection->resource->req_lock);
	rv = _conn_request_state(connection, mask, val, flags);
	spin_unlock_irq(&connection->resource->req_lock);

	return rv;
}