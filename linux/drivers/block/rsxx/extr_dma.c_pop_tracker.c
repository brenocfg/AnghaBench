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
struct dma_tracker_list {int head; int /*<<< orphan*/  lock; TYPE_1__* list; } ;
struct TYPE_2__ {int next_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pop_tracker(struct dma_tracker_list *trackers)
{
	int tag;

	spin_lock(&trackers->lock);
	tag = trackers->head;
	if (tag != -1) {
		trackers->head = trackers->list[tag].next_tag;
		trackers->list[tag].next_tag = -1;
	}
	spin_unlock(&trackers->lock);

	return tag;
}