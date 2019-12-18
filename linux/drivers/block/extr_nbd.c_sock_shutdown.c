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
struct nbd_sock {int /*<<< orphan*/  tx_lock; } ;
struct nbd_device {int /*<<< orphan*/  disk; struct nbd_config* config; } ;
struct nbd_config {int num_connections; struct nbd_sock** socks; int /*<<< orphan*/  runtime_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBD_RT_DISCONNECTED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbd_mark_nsock_dead (struct nbd_device*,struct nbd_sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sock_shutdown(struct nbd_device *nbd)
{
	struct nbd_config *config = nbd->config;
	int i;

	if (config->num_connections == 0)
		return;
	if (test_and_set_bit(NBD_RT_DISCONNECTED, &config->runtime_flags))
		return;

	for (i = 0; i < config->num_connections; i++) {
		struct nbd_sock *nsock = config->socks[i];
		mutex_lock(&nsock->tx_lock);
		nbd_mark_nsock_dead(nbd, nsock, 0);
		mutex_unlock(&nsock->tx_lock);
	}
	dev_warn(disk_to_dev(nbd->disk), "shutting down sockets\n");
}