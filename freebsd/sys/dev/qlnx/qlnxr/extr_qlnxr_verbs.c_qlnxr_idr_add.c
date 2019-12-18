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
typedef  int /*<<< orphan*/  u32 ;
struct qlnxr_dev {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  qpidr; int /*<<< orphan*/ * ha; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QLNX_IS_IWARP (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int idr_get_new_above (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qlnxr_idr_add(struct qlnxr_dev *dev, void *ptr, u32 id)
{
	u32		newid;
	int		rc;
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	if (!QLNX_IS_IWARP(dev))
		return 0;

	do {
		if (!idr_pre_get(&dev->qpidr, GFP_KERNEL)) {
			QL_DPRINT11(ha, "idr_pre_get failed\n");
			return -ENOMEM;
		}

		mtx_lock(&dev->idr_lock);

		rc = idr_get_new_above(&dev->qpidr, ptr, id, &newid);

		mtx_unlock(&dev->idr_lock);

	} while (rc == -EAGAIN);

	QL_DPRINT12(ha, "exit [%d]\n", rc);

	return rc;
}