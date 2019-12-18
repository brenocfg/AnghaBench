#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union ib_gid {int dummy; } ib_gid ;
struct qlnxr_dev {int num_cnq; int /*<<< orphan*/  sgid_lock; int /*<<< orphan*/  idr_lock; TYPE_3__* sgid_tbl; TYPE_3__* sb_array; TYPE_3__* cnq_array; TYPE_1__* ha; int /*<<< orphan*/ * iwarp_wq; } ;
struct qlnxr_cnq {int dummy; } ;
struct ecore_sb_info {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;
struct TYPE_7__ {int /*<<< orphan*/  pbl; } ;

/* Variables and functions */
 int QLNXR_MAX_MSIX ; 
 int QLNXR_MAX_SGID ; 
 scalar_t__ QLNX_IS_IWARP (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_chain_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_free_mem_sb (TYPE_1__*,TYPE_3__*) ; 

__attribute__((used)) static void
qlnxr_free_resources(struct qlnxr_dev *dev)
{
        int i;
	qlnx_host_t *ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter dev->num_cnq = %d\n", dev->num_cnq);

	if (QLNX_IS_IWARP(dev)) {
		if (dev->iwarp_wq != NULL)
			destroy_workqueue(dev->iwarp_wq);
	}

        for (i = 0; i < dev->num_cnq; i++) {
                qlnx_free_mem_sb(dev->ha, &dev->sb_array[i]);
                ecore_chain_free(&dev->ha->cdev, &dev->cnq_array[i].pbl);
        }

	bzero(dev->cnq_array, (sizeof(struct qlnxr_cnq) * QLNXR_MAX_MSIX));
	bzero(dev->sb_array, (sizeof(struct ecore_sb_info) * QLNXR_MAX_MSIX));
	bzero(dev->sgid_tbl, (sizeof(union ib_gid) * QLNXR_MAX_SGID));

	if (mtx_initialized(&dev->idr_lock))
		mtx_destroy(&dev->idr_lock);

	if (mtx_initialized(&dev->sgid_lock))
		mtx_destroy(&dev->sgid_lock);

	QL_DPRINT12(ha, "exit\n");
	return;
}