#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct p_block_desc {int /*<<< orphan*/  blksize; int /*<<< orphan*/  sector; } ;
struct drbd_socket {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  sector; } ;
struct drbd_request {TYPE_2__ i; } ;
struct drbd_peer_device {TYPE_1__* connection; } ;
struct TYPE_3__ {struct drbd_socket data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  P_OUT_OF_SYNC ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct p_block_desc* drbd_prepare_command (struct drbd_peer_device*,struct drbd_socket*) ; 
 int drbd_send_command (struct drbd_peer_device*,struct drbd_socket*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int drbd_send_out_of_sync(struct drbd_peer_device *peer_device, struct drbd_request *req)
{
	struct drbd_socket *sock;
	struct p_block_desc *p;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	if (!p)
		return -EIO;
	p->sector = cpu_to_be64(req->i.sector);
	p->blksize = cpu_to_be32(req->i.size);
	return drbd_send_command(peer_device, sock, P_OUT_OF_SYNC, sizeof(*p), NULL, 0);
}