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
struct vdc_port {int /*<<< orphan*/  tag_set; } ;
struct request_queue {struct vdc_port* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_F_SHOULD_MERGE ; 
 scalar_t__ IS_ERR (struct request_queue*) ; 
 int /*<<< orphan*/  VDC_TX_RING_SIZE ; 
 struct request_queue* blk_mq_init_sq_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdc_mq_ops ; 

__attribute__((used)) static struct request_queue *init_queue(struct vdc_port *port)
{
	struct request_queue *q;

	q = blk_mq_init_sq_queue(&port->tag_set, &vdc_mq_ops, VDC_TX_RING_SIZE,
					BLK_MQ_F_SHOULD_MERGE);
	if (IS_ERR(q))
		return q;

	q->queuedata = port;
	return q;
}