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
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int __mlx4_ib_query_gid (struct ib_device*,int /*<<< orphan*/ ,int,union ib_gid*,int /*<<< orphan*/ ) ; 
 int ib_get_cached_gid (struct ib_device*,int /*<<< orphan*/ ,int,union ib_gid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (union ib_gid*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rdma_cap_roce_gid_table (struct ib_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_protocol_ib (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_protocol_roce (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zgid ; 

__attribute__((used)) static int mlx4_ib_query_gid(struct ib_device *ibdev, u8 port, int index,
			     union ib_gid *gid)
{
	int ret;

	if (rdma_protocol_ib(ibdev, port))
		return __mlx4_ib_query_gid(ibdev, port, index, gid, 0);

	if (!rdma_protocol_roce(ibdev, port))
		return -ENODEV;

	if (!rdma_cap_roce_gid_table(ibdev, port))
		return -ENODEV;

	ret = ib_get_cached_gid(ibdev, port, index, gid, NULL);
	if (ret == -EAGAIN) {
		memcpy(gid, &zgid, sizeof(*gid));
		return 0;
	}

	return ret;
}