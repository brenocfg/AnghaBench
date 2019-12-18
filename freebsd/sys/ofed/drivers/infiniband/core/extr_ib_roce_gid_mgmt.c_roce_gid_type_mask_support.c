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
typedef  int /*<<< orphan*/  u8 ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {unsigned long gid_type; scalar_t__ (* is_supported ) (struct ib_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CAP_TO_GID_TABLE_SIZE ; 
 unsigned long IB_GID_TYPE_IB ; 
 TYPE_1__* PORT_CAP_TO_GID_TYPE ; 
 int /*<<< orphan*/  rdma_protocol_roce (struct ib_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct ib_device*,int /*<<< orphan*/ ) ; 

unsigned long roce_gid_type_mask_support(struct ib_device *ib_dev, u8 port)
{
	int i;
	unsigned int ret_flags = 0;

	if (!rdma_protocol_roce(ib_dev, port))
		return 1UL << IB_GID_TYPE_IB;

	for (i = 0; i < CAP_TO_GID_TABLE_SIZE; i++)
		if (PORT_CAP_TO_GID_TYPE[i].is_supported(ib_dev, port))
			ret_flags |= 1UL << PORT_CAP_TO_GID_TYPE[i].gid_type;

	return ret_flags;
}