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
struct blk_mq_tag_set {int nr_maps; int /*<<< orphan*/  nr_hw_queues; } ;

/* Variables and functions */
 unsigned int max (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int nr_cpu_ids ; 

__attribute__((used)) static unsigned int nr_hw_queues(struct blk_mq_tag_set *set)
{
	if (set->nr_maps == 1)
		return nr_cpu_ids;

	return max(set->nr_hw_queues, nr_cpu_ids);
}