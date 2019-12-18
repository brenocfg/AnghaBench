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
struct p_data {int /*<<< orphan*/  block_id; int /*<<< orphan*/  sector; } ;
struct drbd_peer_device {TYPE_1__* connection; } ;
typedef  enum drbd_packet { ____Placeholder_drbd_packet } drbd_packet ;
struct TYPE_2__ {scalar_t__ peer_integrity_tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  _drbd_send_ack (struct drbd_peer_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 scalar_t__ crypto_shash_digestsize (scalar_t__) ; 

void drbd_send_ack_dp(struct drbd_peer_device *peer_device, enum drbd_packet cmd,
		      struct p_data *dp, int data_size)
{
	if (peer_device->connection->peer_integrity_tfm)
		data_size -= crypto_shash_digestsize(peer_device->connection->peer_integrity_tfm);
	_drbd_send_ack(peer_device, cmd, dp->sector, cpu_to_be32(data_size),
		       dp->block_id);
}