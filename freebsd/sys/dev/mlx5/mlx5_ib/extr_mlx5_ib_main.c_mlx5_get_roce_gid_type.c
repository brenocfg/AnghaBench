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
struct mlx5_ib_dev {int /*<<< orphan*/  ib_dev; } ;
struct ib_gid_attr {int gid_type; int /*<<< orphan*/  ndev; } ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int ib_get_cached_gid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,union ib_gid*,struct ib_gid_attr*) ; 

int mlx5_get_roce_gid_type(struct mlx5_ib_dev *dev, u8 port_num,
			   int index, enum ib_gid_type *gid_type)
{
	struct ib_gid_attr attr;
	union ib_gid gid;
	int ret;

	ret = ib_get_cached_gid(&dev->ib_dev, port_num, index, &gid, &attr);
	if (ret)
		return ret;

	if (!attr.ndev)
		return -ENODEV;

	dev_put(attr.ndev);

	*gid_type = attr.gid_type;

	return 0;
}