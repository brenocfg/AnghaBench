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

int
ixl_pf_qmgr_get_num_free(struct ixl_pf_qmgr *qmgr)
{
	int count = 0;

	for (int i = 0; i < qmgr->num_queues; i++) {
		if (!qmgr->qinfo[i].allocated)
			count++;
	}

	return (count);
}