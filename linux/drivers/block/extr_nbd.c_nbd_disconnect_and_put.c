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
struct nbd_device {TYPE_1__* config; int /*<<< orphan*/  recv_workq; int /*<<< orphan*/  config_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBD_RT_HAS_CONFIG_REF ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbd_clear_sock (struct nbd_device*) ; 
 int /*<<< orphan*/  nbd_config_put (struct nbd_device*) ; 
 int /*<<< orphan*/  nbd_disconnect (struct nbd_device*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nbd_disconnect_and_put(struct nbd_device *nbd)
{
	mutex_lock(&nbd->config_lock);
	nbd_disconnect(nbd);
	nbd_clear_sock(nbd);
	mutex_unlock(&nbd->config_lock);
	/*
	 * Make sure recv thread has finished, so it does not drop the last
	 * config ref and try to destroy the workqueue from inside the work
	 * queue.
	 */
	flush_workqueue(nbd->recv_workq);
	if (test_and_clear_bit(NBD_RT_HAS_CONFIG_REF,
			       &nbd->config->runtime_flags))
		nbd_config_put(nbd);
}