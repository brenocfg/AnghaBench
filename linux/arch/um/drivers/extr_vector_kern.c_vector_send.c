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
struct vector_queue {int max_depth; int queue_depth; int head; int /*<<< orphan*/  head_lock; int /*<<< orphan*/  dev; struct mmsghdr* mmsg_vector; int /*<<< orphan*/  tail_lock; } ;
struct TYPE_4__ {int tx_queue_max; int tx_queue_running_average; int /*<<< orphan*/  tx_restart_queue; } ;
struct vector_private {int in_write_poll; int in_error; int /*<<< orphan*/  tx_poll; TYPE_2__ estats; int /*<<< orphan*/  dev; TYPE_1__* fds; } ;
struct mmsghdr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_fd; } ;

/* Variables and functions */
 int consume_vector_skbs (struct vector_queue*,int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct vector_private* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_trans_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int uml_vector_sendmmsg (int /*<<< orphan*/ ,struct mmsghdr*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vector_send(struct vector_queue *qi)
{
	struct vector_private *vp = netdev_priv(qi->dev);
	struct mmsghdr *send_from;
	int result = 0, send_len, queue_depth = qi->max_depth;

	if (spin_trylock(&qi->head_lock)) {
		if (spin_trylock(&qi->tail_lock)) {
			/* update queue_depth to current value */
			queue_depth = qi->queue_depth;
			spin_unlock(&qi->tail_lock);
			while (queue_depth > 0) {
				/* Calculate the start of the vector */
				send_len = queue_depth;
				send_from = qi->mmsg_vector;
				send_from += qi->head;
				/* Adjust vector size if wraparound */
				if (send_len + qi->head > qi->max_depth)
					send_len = qi->max_depth - qi->head;
				/* Try to TX as many packets as possible */
				if (send_len > 0) {
					result = uml_vector_sendmmsg(
						 vp->fds->tx_fd,
						 send_from,
						 send_len,
						 0
					);
					vp->in_write_poll =
						(result != send_len);
				}
				/* For some of the sendmmsg error scenarios
				 * we may end being unsure in the TX success
				 * for all packets. It is safer to declare
				 * them all TX-ed and blame the network.
				 */
				if (result < 0) {
					if (net_ratelimit())
						netdev_err(vp->dev, "sendmmsg err=%i\n",
							result);
					vp->in_error = true;
					result = send_len;
				}
				if (result > 0) {
					queue_depth =
						consume_vector_skbs(qi, result);
					/* This is equivalent to an TX IRQ.
					 * Restart the upper layers to feed us
					 * more packets.
					 */
					if (result > vp->estats.tx_queue_max)
						vp->estats.tx_queue_max = result;
					vp->estats.tx_queue_running_average =
						(vp->estats.tx_queue_running_average + result) >> 1;
				}
				netif_trans_update(qi->dev);
				netif_wake_queue(qi->dev);
				/* if TX is busy, break out of the send loop,
				 *  poll write IRQ will reschedule xmit for us
				 */
				if (result != send_len) {
					vp->estats.tx_restart_queue++;
					break;
				}
			}
		}
		spin_unlock(&qi->head_lock);
	} else {
		tasklet_schedule(&vp->tx_poll);
	}
	return queue_depth;
}