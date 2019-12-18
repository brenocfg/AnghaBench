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
struct vio_dring_state {int dummy; } ;
struct TYPE_3__ {struct vio_dring_state* drings; } ;
struct vdc_port {TYPE_2__* disk; TYPE_1__ vio; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int VDC_TX_RING_SIZE ; 
 size_t VIO_DRIVER_TX_RING ; 
 int /*<<< orphan*/  blk_mq_start_stopped_hw_queues (int /*<<< orphan*/ ,int) ; 
 int vdc_tx_dring_avail (struct vio_dring_state*) ; 

__attribute__((used)) static void vdc_blk_queue_start(struct vdc_port *port)
{
	struct vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];

	/* restart blk queue when ring is half emptied. also called after
	 * handshake completes, so check for initial handshake before we've
	 * allocated a disk.
	 */
	if (port->disk && vdc_tx_dring_avail(dr) * 100 / VDC_TX_RING_SIZE >= 50)
		blk_mq_start_stopped_hw_queues(port->disk->queue, true);
}