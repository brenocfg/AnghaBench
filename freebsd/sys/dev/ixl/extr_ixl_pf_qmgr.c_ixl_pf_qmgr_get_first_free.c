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
typedef  int u16 ;
struct ixl_pf_qmgr {int num_queues; TYPE_1__* qinfo; } ;
struct TYPE_2__ {scalar_t__ allocated; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 

int
ixl_pf_qmgr_get_first_free(struct ixl_pf_qmgr *qmgr, u16 start)
{
	int i;

	if (start > qmgr->num_queues - 1)
		return (-EINVAL);

	for (i = start; i < qmgr->num_queues; i++) {
		if (qmgr->qinfo[i].allocated)
			continue;
		else
			return (i);
	}

	// No free queues
	return (-ENOSPC);
}