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
struct nullb {int nr_queues; int /*<<< orphan*/ * queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_queues(struct nullb *nullb)
{
	int i;

	for (i = 0; i < nullb->nr_queues; i++)
		cleanup_queue(&nullb->queues[i]);

	kfree(nullb->queues);
}