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
struct vector_private {int opened; int options; int /*<<< orphan*/  tl; int /*<<< orphan*/  unit; TYPE_2__* fds; int /*<<< orphan*/  bpf; void* tx_irq; void* rx_irq; int /*<<< orphan*/ * header_txbuffer; int /*<<< orphan*/  header_size; int /*<<< orphan*/  parsed; void* tx_queue; int /*<<< orphan*/ * header_rxbuffer; int /*<<< orphan*/  rx_header_size; TYPE_1__* rx_queue; int /*<<< orphan*/  lock; } ;
struct vector_device {int opened; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; void* irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_fd; int /*<<< orphan*/  tx_fd; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue_depth; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETUNREACH ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_READ ; 
 int /*<<< orphan*/  IRQ_WRITE ; 
 int /*<<< orphan*/  MAX_IOV_SIZE ; 
 void* VECTOR_BASE_IRQ ; 
 int VECTOR_BPF ; 
 int VECTOR_IRQ_SPACE ; 
 int VECTOR_QDISC_BYPASS ; 
 int VECTOR_RX ; 
 int VECTOR_TX ; 
 int /*<<< orphan*/  add_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ build_transport_data (struct vector_private*) ; 
 void* create_queue (struct vector_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vector_device* find_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_depth (int /*<<< orphan*/ ) ; 
 int irq_rr ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct vector_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int um_request_irq (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  uml_raw_enable_qdisc_bypass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uml_vector_default_bpf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* uml_vector_user_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vector_net_close (struct net_device*) ; 
 int /*<<< orphan*/  vector_reset_stats (struct vector_private*) ; 
 int /*<<< orphan*/  vector_rx (struct vector_private*) ; 
 int /*<<< orphan*/  vector_rx_interrupt ; 
 int /*<<< orphan*/  vector_tx_interrupt ; 

__attribute__((used)) static int vector_net_open(struct net_device *dev)
{
	struct vector_private *vp = netdev_priv(dev);
	unsigned long flags;
	int err = -EINVAL;
	struct vector_device *vdevice;

	spin_lock_irqsave(&vp->lock, flags);
	if (vp->opened) {
		spin_unlock_irqrestore(&vp->lock, flags);
		return -ENXIO;
	}
	vp->opened = true;
	spin_unlock_irqrestore(&vp->lock, flags);

	vp->fds = uml_vector_user_open(vp->unit, vp->parsed);

	if (vp->fds == NULL)
		goto out_close;

	if (build_transport_data(vp) < 0)
		goto out_close;

	if ((vp->options & VECTOR_RX) > 0) {
		vp->rx_queue = create_queue(
			vp,
			get_depth(vp->parsed),
			vp->rx_header_size,
			MAX_IOV_SIZE
		);
		vp->rx_queue->queue_depth = get_depth(vp->parsed);
	} else {
		vp->header_rxbuffer = kmalloc(
			vp->rx_header_size,
			GFP_KERNEL
		);
		if (vp->header_rxbuffer == NULL)
			goto out_close;
	}
	if ((vp->options & VECTOR_TX) > 0) {
		vp->tx_queue = create_queue(
			vp,
			get_depth(vp->parsed),
			vp->header_size,
			MAX_IOV_SIZE
		);
	} else {
		vp->header_txbuffer = kmalloc(vp->header_size, GFP_KERNEL);
		if (vp->header_txbuffer == NULL)
			goto out_close;
	}

	/* READ IRQ */
	err = um_request_irq(
		irq_rr + VECTOR_BASE_IRQ, vp->fds->rx_fd,
			IRQ_READ, vector_rx_interrupt,
			IRQF_SHARED, dev->name, dev);
	if (err != 0) {
		netdev_err(dev, "vector_open: failed to get rx irq(%d)\n", err);
		err = -ENETUNREACH;
		goto out_close;
	}
	vp->rx_irq = irq_rr + VECTOR_BASE_IRQ;
	dev->irq = irq_rr + VECTOR_BASE_IRQ;
	irq_rr = (irq_rr + 1) % VECTOR_IRQ_SPACE;

	/* WRITE IRQ - we need it only if we have vector TX */
	if ((vp->options & VECTOR_TX) > 0) {
		err = um_request_irq(
			irq_rr + VECTOR_BASE_IRQ, vp->fds->tx_fd,
				IRQ_WRITE, vector_tx_interrupt,
				IRQF_SHARED, dev->name, dev);
		if (err != 0) {
			netdev_err(dev,
				"vector_open: failed to get tx irq(%d)\n", err);
			err = -ENETUNREACH;
			goto out_close;
		}
		vp->tx_irq = irq_rr + VECTOR_BASE_IRQ;
		irq_rr = (irq_rr + 1) % VECTOR_IRQ_SPACE;
	}

	if ((vp->options & VECTOR_QDISC_BYPASS) != 0) {
		if (!uml_raw_enable_qdisc_bypass(vp->fds->rx_fd))
			vp->options |= VECTOR_BPF;
	}
	if ((vp->options & VECTOR_BPF) != 0)
		vp->bpf = uml_vector_default_bpf(vp->fds->rx_fd, dev->dev_addr);

	netif_start_queue(dev);

	/* clear buffer - it can happen that the host side of the interface
	 * is full when we get here. In this case, new data is never queued,
	 * SIGIOs never arrive, and the net never works.
	 */

	vector_rx(vp);

	vector_reset_stats(vp);
	vdevice = find_device(vp->unit);
	vdevice->opened = 1;

	if ((vp->options & VECTOR_TX) != 0)
		add_timer(&vp->tl);
	return 0;
out_close:
	vector_net_close(dev);
	return err;
}