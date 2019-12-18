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
struct nullb_queue {int /*<<< orphan*/  dev; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  wait; } ;
struct nullb {int /*<<< orphan*/  dev; int /*<<< orphan*/  queue_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void null_init_queue(struct nullb *nullb, struct nullb_queue *nq)
{
	BUG_ON(!nullb);
	BUG_ON(!nq);

	init_waitqueue_head(&nq->wait);
	nq->queue_depth = nullb->queue_depth;
	nq->dev = nullb->dev;
}