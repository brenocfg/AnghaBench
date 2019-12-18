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
struct nullb_queue {int dummy; } ;
struct nullb {TYPE_1__* dev; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  queues; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_queue_depth; int /*<<< orphan*/  submit_queues; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_queues(struct nullb *nullb)
{
	nullb->queues = kcalloc(nullb->dev->submit_queues,
				sizeof(struct nullb_queue),
				GFP_KERNEL);
	if (!nullb->queues)
		return -ENOMEM;

	nullb->queue_depth = nullb->dev->hw_queue_depth;

	return 0;
}