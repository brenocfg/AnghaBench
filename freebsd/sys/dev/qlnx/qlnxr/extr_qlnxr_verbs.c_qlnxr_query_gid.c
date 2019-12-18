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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u8 ;
struct qlnxr_dev {int /*<<< orphan*/ * sgid_tbl; int /*<<< orphan*/ * ha; } ;
struct ib_device {scalar_t__ del_gid; scalar_t__ add_gid; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENODEV ; 
 int QLNXR_MAX_SGID ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,int) ; 
 struct qlnxr_dev* get_qlnxr_dev (struct ib_device*) ; 
 int ib_get_cached_gid (struct ib_device*,int /*<<< orphan*/ ,int,union ib_gid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (union ib_gid*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (union ib_gid*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rdma_protocol_roce (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zgid ; 

int
qlnxr_query_gid(struct ib_device *ibdev, u8 port, int index,
	union ib_gid *sgid)
{
	struct qlnxr_dev	*dev;
	qlnx_host_t		*ha;

	dev = get_qlnxr_dev(ibdev);
	ha = dev->ha;
	QL_DPRINT12(ha, "enter index: %d\n", index);
#if 0
	int ret = 0;
	/* @@@: if DEFINE_ROCE_GID_TABLE to be used here */
	//if (!rdma_cap_roce_gid_table(ibdev, port)) {
	if (!(rdma_protocol_roce(ibdev, port) &&
		ibdev->add_gid && ibdev->del_gid)) {
		QL_DPRINT11(ha, "acquire gid failed\n");
		return -ENODEV;
	}

	ret = ib_get_cached_gid(ibdev, port, index, sgid, NULL);
	if (ret == -EAGAIN) {
		memcpy(sgid, &zgid, sizeof(*sgid));
		return 0;
	}
#endif
	if ((index >= QLNXR_MAX_SGID) || (index < 0)) {
		QL_DPRINT12(ha, "invalid gid index %d\n", index);
		memset(sgid, 0, sizeof(*sgid));
		return -EINVAL;
	}
	memcpy(sgid, &dev->sgid_tbl[index], sizeof(*sgid));

	QL_DPRINT12(ha, "exit : %p\n", sgid);

	return 0;
}