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
struct TYPE_2__ {int /*<<< orphan*/  member_0; } ;
union ib_gid {TYPE_1__ member_0; } ;
struct qlnxr_dev {int /*<<< orphan*/  sgid_lock; int /*<<< orphan*/  ha; int /*<<< orphan*/ * sgid_tbl; } ;

/* Variables and functions */
 int QLNXR_MAX_SGID ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,union ib_gid*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union ib_gid*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
qlnxr_add_sgid(struct qlnxr_dev *dev, union ib_gid *new_sgid)
{
	union ib_gid zero_sgid = { { 0 } };
	int i;
	//unsigned long flags;
	mtx_lock(&dev->sgid_lock);
	for (i = 0; i < QLNXR_MAX_SGID; i++) {
		if (!memcmp(&dev->sgid_tbl[i], &zero_sgid,
				sizeof(union ib_gid))) {
			/* found free entry */
			memcpy(&dev->sgid_tbl[i], new_sgid,
				sizeof(union ib_gid));
			QL_DPRINT12(dev->ha, "copying sgid : %llx\n",
					*new_sgid);
			mtx_unlock(&dev->sgid_lock);
			//TODO ib_dispatch event here?
			return true;
		} else if (!memcmp(&dev->sgid_tbl[i], new_sgid,
				sizeof(union ib_gid))) {
			/* entry already present, no addition required */
			mtx_unlock(&dev->sgid_lock);
			QL_DPRINT12(dev->ha, "sgid present : %llx\n",
					*new_sgid);
			return false;
		}
	}	
	if (i == QLNXR_MAX_SGID) {
		QL_DPRINT12(dev->ha, "didn't find an empty entry in sgid_tbl\n");
	}
	mtx_unlock(&dev->sgid_lock);
	return false;
}