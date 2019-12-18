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
struct task_struct {int dummy; } ;
struct drbd_connection {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  _try_outdate_peer_async ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  drbd_destroy_connection ; 
 int /*<<< orphan*/  drbd_err (struct drbd_connection*,char*) ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct drbd_connection*,char*) ; 

void conn_try_outdate_peer_async(struct drbd_connection *connection)
{
	struct task_struct *opa;

	kref_get(&connection->kref);
	/* We may have just sent a signal to this thread
	 * to get it out of some blocking network function.
	 * Clear signals; otherwise kthread_run(), which internally uses
	 * wait_on_completion_killable(), will mistake our pending signal
	 * for a new fatal signal and fail. */
	flush_signals(current);
	opa = kthread_run(_try_outdate_peer_async, connection, "drbd_async_h");
	if (IS_ERR(opa)) {
		drbd_err(connection, "out of mem, failed to invoke fence-peer helper\n");
		kref_put(&connection->kref, drbd_destroy_connection);
	}
}