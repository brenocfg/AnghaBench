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
struct TYPE_4__ {int /*<<< orphan*/  fifo_lo; int /*<<< orphan*/  fifo_hi; int /*<<< orphan*/  sspd; int /*<<< orphan*/  max_rec; int /*<<< orphan*/  uniq_id; } ;
union fwnet_hwaddr {TYPE_2__ uc; } ;
struct net_device {unsigned int mtu; unsigned int max_mtu; int /*<<< orphan*/  dev; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  broadcast; scalar_t__ dev_addr; int /*<<< orphan*/  min_mtu; } ;
struct ieee1394_device_id {int dummy; } ;
struct TYPE_3__ {int offset; } ;
struct fwnet_device {int local_fifo; int /*<<< orphan*/  dev_link; struct fw_card* card; TYPE_1__ handler; struct net_device* netdev; int /*<<< orphan*/  peer_list; scalar_t__ queued_datagrams; scalar_t__ broadcast_xmt_datagramlabel; scalar_t__ broadcast_xmt_max_payload; int /*<<< orphan*/ * broadcast_rcv_context; int /*<<< orphan*/  broadcast_state; int /*<<< orphan*/  lock; } ;
struct fw_unit {int dummy; } ;
struct fw_device {struct fw_card* card; } ;
struct fw_card {int /*<<< orphan*/  device; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  max_receive; int /*<<< orphan*/  guid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int /*<<< orphan*/  FWNET_BROADCAST_ERROR ; 
 int FWNET_NO_FIFO_ADDR ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct fw_device* fw_parent_device (struct fw_unit*) ; 
 int fwnet_add_peer (struct fwnet_device*,struct fw_unit*,struct fw_device*) ; 
 struct fwnet_device* fwnet_dev_find (struct fw_card*) ; 
 int /*<<< orphan*/  fwnet_device_list ; 
 int /*<<< orphan*/  fwnet_device_mutex ; 
 int fwnet_fifo_start (struct fwnet_device*) ; 
 int /*<<< orphan*/  fwnet_fifo_stop (struct fwnet_device*) ; 
 int /*<<< orphan*/  fwnet_init_dev ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fwnet_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int fwnet_probe(struct fw_unit *unit,
		       const struct ieee1394_device_id *id)
{
	struct fw_device *device = fw_parent_device(unit);
	struct fw_card *card = device->card;
	struct net_device *net;
	bool allocated_netdev = false;
	struct fwnet_device *dev;
	int ret;
	union fwnet_hwaddr *ha;

	mutex_lock(&fwnet_device_mutex);

	dev = fwnet_dev_find(card);
	if (dev) {
		net = dev->netdev;
		goto have_dev;
	}

	net = alloc_netdev(sizeof(*dev), "firewire%d", NET_NAME_UNKNOWN,
			   fwnet_init_dev);
	if (net == NULL) {
		mutex_unlock(&fwnet_device_mutex);
		return -ENOMEM;
	}

	allocated_netdev = true;
	SET_NETDEV_DEV(net, card->device);
	dev = netdev_priv(net);

	spin_lock_init(&dev->lock);
	dev->broadcast_state = FWNET_BROADCAST_ERROR;
	dev->broadcast_rcv_context = NULL;
	dev->broadcast_xmt_max_payload = 0;
	dev->broadcast_xmt_datagramlabel = 0;
	dev->local_fifo = FWNET_NO_FIFO_ADDR;
	dev->queued_datagrams = 0;
	INIT_LIST_HEAD(&dev->peer_list);
	dev->card = card;
	dev->netdev = net;

	ret = fwnet_fifo_start(dev);
	if (ret < 0)
		goto out;
	dev->local_fifo = dev->handler.offset;

	/*
	 * default MTU: RFC 2734 cl. 4, RFC 3146 cl. 4
	 * maximum MTU: RFC 2734 cl. 4.2, fragment encapsulation header's
	 *              maximum possible datagram_size + 1 = 0xfff + 1
	 */
	net->mtu = 1500U;
	net->min_mtu = ETH_MIN_MTU;
	net->max_mtu = 4096U;

	/* Set our hardware address while we're at it */
	ha = (union fwnet_hwaddr *)net->dev_addr;
	put_unaligned_be64(card->guid, &ha->uc.uniq_id);
	ha->uc.max_rec = dev->card->max_receive;
	ha->uc.sspd = dev->card->link_speed;
	put_unaligned_be16(dev->local_fifo >> 32, &ha->uc.fifo_hi);
	put_unaligned_be32(dev->local_fifo & 0xffffffff, &ha->uc.fifo_lo);

	memset(net->broadcast, -1, net->addr_len);

	ret = register_netdev(net);
	if (ret)
		goto out;

	list_add_tail(&dev->dev_link, &fwnet_device_list);
	dev_notice(&net->dev, "IP over IEEE 1394 on card %s\n",
		   dev_name(card->device));
 have_dev:
	ret = fwnet_add_peer(dev, unit, device);
	if (ret && allocated_netdev) {
		unregister_netdev(net);
		list_del(&dev->dev_link);
 out:
		fwnet_fifo_stop(dev);
		free_netdev(net);
	}

	mutex_unlock(&fwnet_device_mutex);

	return ret;
}