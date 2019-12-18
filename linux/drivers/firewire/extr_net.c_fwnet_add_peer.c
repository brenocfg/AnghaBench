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
typedef  int u64 ;
struct fwnet_peer {int guid; int /*<<< orphan*/  peer_link; int /*<<< orphan*/  node_id; int /*<<< orphan*/  generation; int /*<<< orphan*/  speed; int /*<<< orphan*/  max_payload; scalar_t__ datagram_label; scalar_t__ pdg_size; int /*<<< orphan*/  pd_list; struct fwnet_device* dev; } ;
struct fwnet_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  peer_count; int /*<<< orphan*/  peer_list; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;
struct fw_device {int* config_rom; int /*<<< orphan*/  node_id; int /*<<< orphan*/  generation; int /*<<< orphan*/  max_rec; int /*<<< orphan*/  max_speed; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct fwnet_peer*) ; 
 int /*<<< orphan*/  fwnet_max_payload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fwnet_peer* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_carrier_state (struct fwnet_device*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fwnet_add_peer(struct fwnet_device *dev,
			  struct fw_unit *unit, struct fw_device *device)
{
	struct fwnet_peer *peer;

	peer = kmalloc(sizeof(*peer), GFP_KERNEL);
	if (!peer)
		return -ENOMEM;

	dev_set_drvdata(&unit->device, peer);

	peer->dev = dev;
	peer->guid = (u64)device->config_rom[3] << 32 | device->config_rom[4];
	INIT_LIST_HEAD(&peer->pd_list);
	peer->pdg_size = 0;
	peer->datagram_label = 0;
	peer->speed = device->max_speed;
	peer->max_payload = fwnet_max_payload(device->max_rec, peer->speed);

	peer->generation = device->generation;
	smp_rmb();
	peer->node_id = device->node_id;

	spin_lock_irq(&dev->lock);
	list_add_tail(&peer->peer_link, &dev->peer_list);
	dev->peer_count++;
	set_carrier_state(dev);
	spin_unlock_irq(&dev->lock);

	return 0;
}