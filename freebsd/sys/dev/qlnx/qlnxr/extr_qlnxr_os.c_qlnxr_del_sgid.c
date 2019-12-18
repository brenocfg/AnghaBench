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
struct TYPE_2__ {int /*<<< orphan*/  subnet_prefix; int /*<<< orphan*/  interface_id; } ;
union ib_gid {TYPE_1__ global; } ;
struct qlnxr_dev {int /*<<< orphan*/  sgid_lock; int /*<<< orphan*/ * sgid_tbl; int /*<<< orphan*/  ha; } ;

/* Variables and functions */
 int QLNXR_MAX_SGID ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,union ib_gid*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool qlnxr_del_sgid(struct qlnxr_dev *dev, union ib_gid *gid)
{
	int found = false;
	int i;
	//unsigned long flags;

	QL_DPRINT12(dev->ha, "removing gid %llx %llx\n",
			gid->global.interface_id,
			gid->global.subnet_prefix);
	mtx_lock(&dev->sgid_lock);
	/* first is the default sgid which cannot be deleted */
	for (i = 1; i < QLNXR_MAX_SGID; i++) {
		if (!memcmp(&dev->sgid_tbl[i], gid, sizeof(union ib_gid))) {
			/* found matching entry */
			memset(&dev->sgid_tbl[i], 0, sizeof(union ib_gid));
			found = true;
			break;
		}
	}
	mtx_unlock(&dev->sgid_lock);

	return found;
}