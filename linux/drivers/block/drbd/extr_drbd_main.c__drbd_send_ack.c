#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct p_block_ack {int /*<<< orphan*/  seq_num; int /*<<< orphan*/  blksize; void* block_id; void* sector; } ;
struct drbd_socket {int dummy; } ;
struct drbd_peer_device {TYPE_3__* device; TYPE_1__* connection; } ;
typedef  enum drbd_packet { ____Placeholder_drbd_packet } drbd_packet ;
struct TYPE_5__ {scalar_t__ conn; } ;
struct TYPE_6__ {int /*<<< orphan*/  packet_seq; TYPE_2__ state; } ;
struct TYPE_4__ {struct drbd_socket meta; } ;

/* Variables and functions */
 scalar_t__ C_CONNECTED ; 
 int EIO ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct p_block_ack* drbd_prepare_command (struct drbd_peer_device*,struct drbd_socket*) ; 
 int drbd_send_command (struct drbd_peer_device*,struct drbd_socket*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _drbd_send_ack(struct drbd_peer_device *peer_device, enum drbd_packet cmd,
			  u64 sector, u32 blksize, u64 block_id)
{
	struct drbd_socket *sock;
	struct p_block_ack *p;

	if (peer_device->device->state.conn < C_CONNECTED)
		return -EIO;

	sock = &peer_device->connection->meta;
	p = drbd_prepare_command(peer_device, sock);
	if (!p)
		return -EIO;
	p->sector = sector;
	p->block_id = block_id;
	p->blksize = blksize;
	p->seq_num = cpu_to_be32(atomic_inc_return(&peer_device->device->packet_seq));
	return drbd_send_command(peer_device, sock, cmd, sizeof(*p), NULL, 0);
}