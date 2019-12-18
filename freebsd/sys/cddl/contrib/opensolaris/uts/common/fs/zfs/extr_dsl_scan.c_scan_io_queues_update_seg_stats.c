#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  q_segs_this_txg; int /*<<< orphan*/  q_total_seg_size_this_txg; } ;
typedef  TYPE_1__ dsl_scan_io_queue_t ;

/* Variables and functions */

__attribute__((used)) static void
scan_io_queues_update_seg_stats(dsl_scan_io_queue_t *q, uint64_t start,
    uint64_t end)
{
	q->q_total_seg_size_this_txg += end - start;
	q->q_segs_this_txg++;
}