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
struct TYPE_2__ {int /*<<< orphan*/  num_active; int /*<<< orphan*/  num_allocated; } ;
struct ixl_vf {int vf_num; TYPE_1__ qtag; } ;
struct ixl_pf {int /*<<< orphan*/  qmgr; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOSPC ; 
 int IAVF_MAX_QUEUES ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ixl_dbg_iov (struct ixl_pf*,char*,int,...) ; 
 int ixl_pf_qmgr_alloc_scattered (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ixl_pf_qmgr_get_num_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ixl_vf_reserve_queues(struct ixl_pf *pf, struct ixl_vf *vf, int num_queues)
{
	device_t dev = pf->dev;
	int error;

	/* Validate, and clamp value if invalid */
	if (num_queues < 1 || num_queues > 16)
		device_printf(dev, "Invalid num-queues (%d) for VF %d\n",
		    num_queues, vf->vf_num);
	if (num_queues < 1) {
		device_printf(dev, "Setting VF %d num-queues to 1\n", vf->vf_num);
		num_queues = 1;
	} else if (num_queues > IAVF_MAX_QUEUES) {
		device_printf(dev, "Setting VF %d num-queues to %d\n", vf->vf_num, IAVF_MAX_QUEUES);
		num_queues = IAVF_MAX_QUEUES;
	}
	error = ixl_pf_qmgr_alloc_scattered(&pf->qmgr, num_queues, &vf->qtag);
	if (error) {
		device_printf(dev, "Error allocating %d queues for VF %d's VSI\n",
		    num_queues, vf->vf_num);
		return (ENOSPC);
	}

	ixl_dbg_iov(pf, "VF %d: %d allocated, %d active\n",
	    vf->vf_num, vf->qtag.num_allocated, vf->qtag.num_active);
	ixl_dbg_iov(pf, "Unallocated total: %d\n", ixl_pf_qmgr_get_num_free(&pf->qmgr));

	return (0);
}