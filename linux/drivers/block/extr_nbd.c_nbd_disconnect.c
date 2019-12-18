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
struct nbd_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  disk; struct nbd_config* config; } ;
struct nbd_config {int /*<<< orphan*/  runtime_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBD_DISCONNECT_REQUESTED ; 
 int /*<<< orphan*/  NBD_RT_DISCONNECT_REQUESTED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_disconnects (struct nbd_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nbd_disconnect(struct nbd_device *nbd)
{
	struct nbd_config *config = nbd->config;

	dev_info(disk_to_dev(nbd->disk), "NBD_DISCONNECT\n");
	set_bit(NBD_RT_DISCONNECT_REQUESTED, &config->runtime_flags);
	set_bit(NBD_DISCONNECT_REQUESTED, &nbd->flags);
	send_disconnects(nbd);
	return 0;
}