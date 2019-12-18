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
struct ixl_pf_qmgr {int num_queues; TYPE_1__* qinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  allocated; } ;

/* Variables and functions */

__attribute__((used)) static int
ixl_pf_qmgr_find_free_contiguous_block(struct ixl_pf_qmgr *qmgr, int num)
{
	int i;
	int count = 0;
	bool block_started = false;
	int possible_start;

	for (i = 0; i < qmgr->num_queues; i++) {
		if (!qmgr->qinfo[i].allocated) {
			if (!block_started) {
				block_started = true;
				possible_start = i;
			}
			count++;
			if (count == num)
				return (possible_start);
		} else { /* this queue is already allocated */
			block_started = false;
			count = 0;
		}
	}

	/* Can't find a contiguous block of the requested size */
	return (-1);
}