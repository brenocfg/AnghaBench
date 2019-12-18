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
struct ixl_pf_qmgr {int num_queues; } ;

/* Variables and functions */

int
ixl_pf_qmgr_get_num_queues(struct ixl_pf_qmgr *qmgr)
{
	return (qmgr->num_queues);
}