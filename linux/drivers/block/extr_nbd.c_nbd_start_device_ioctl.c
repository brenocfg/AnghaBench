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
struct nbd_device {int /*<<< orphan*/  config_lock; int /*<<< orphan*/  recv_workq; struct nbd_config* config; } ;
struct nbd_config {int /*<<< orphan*/  runtime_flags; int /*<<< orphan*/  recv_threads; int /*<<< orphan*/  recv_wq; } ;
struct block_device {int bd_invalidated; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  NBD_RT_DISCONNECT_REQUESTED ; 
 int /*<<< orphan*/  NBD_RT_TIMEDOUT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 scalar_t__ max_part ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbd_bdev_reset (struct block_device*) ; 
 int nbd_start_device (struct nbd_device*) ; 
 int /*<<< orphan*/  sock_shutdown (struct nbd_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nbd_start_device_ioctl(struct nbd_device *nbd, struct block_device *bdev)
{
	struct nbd_config *config = nbd->config;
	int ret;

	ret = nbd_start_device(nbd);
	if (ret)
		return ret;

	if (max_part)
		bdev->bd_invalidated = 1;
	mutex_unlock(&nbd->config_lock);
	ret = wait_event_interruptible(config->recv_wq,
					 atomic_read(&config->recv_threads) == 0);
	if (ret) {
		sock_shutdown(nbd);
		flush_workqueue(nbd->recv_workq);
	}
	mutex_lock(&nbd->config_lock);
	nbd_bdev_reset(bdev);
	/* user requested, ignore socket errors */
	if (test_bit(NBD_RT_DISCONNECT_REQUESTED, &config->runtime_flags))
		ret = 0;
	if (test_bit(NBD_RT_TIMEDOUT, &config->runtime_flags))
		ret = -ETIMEDOUT;
	return ret;
}