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
struct blk_queue_stats {int /*<<< orphan*/  callbacks; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct blk_queue_stats*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void blk_free_queue_stats(struct blk_queue_stats *stats)
{
	if (!stats)
		return;

	WARN_ON(!list_empty(&stats->callbacks));

	kfree(stats);
}