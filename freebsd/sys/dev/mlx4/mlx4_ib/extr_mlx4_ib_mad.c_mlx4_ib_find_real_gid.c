#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_8__ {TYPE_3__* demux; } ;
struct mlx4_ib_dev {TYPE_4__ sriov; TYPE_2__* dev; } ;
struct ib_device {int dummy; } ;
typedef  scalar_t__ __be64 ;
struct TYPE_7__ {scalar_t__* guid_cache; } ;
struct TYPE_5__ {int sqp_demux; } ;
struct TYPE_6__ {TYPE_1__ caps; } ;

/* Variables and functions */
 struct mlx4_ib_dev* to_mdev (struct ib_device*) ; 

int mlx4_ib_find_real_gid(struct ib_device *ibdev, u8 port, __be64 guid)
{
	struct mlx4_ib_dev *dev = to_mdev(ibdev);
	int i;

	for (i = 0; i < dev->dev->caps.sqp_demux; i++) {
		if (dev->sriov.demux[port - 1].guid_cache[i] == guid)
			return i;
	}
	return -1;
}