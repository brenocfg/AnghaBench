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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QLNXR_ROCE_PKEY_DEFAULT ; 
 int /*<<< orphan*/  QLNXR_ROCE_PKEY_TABLE_LEN ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 struct qlnxr_dev* get_qlnxr_dev (struct ib_device*) ; 

int
qlnxr_query_pkey(struct ib_device *ibdev, u8 port, u16 index, u16 *pkey)
{
	struct qlnxr_dev	*dev;
	qlnx_host_t		*ha;

	dev = get_qlnxr_dev(ibdev);
	ha = dev->ha;

	QL_DPRINT12(ha, "enter index = 0x%x\n", index);

	if (index > QLNXR_ROCE_PKEY_TABLE_LEN) 
		return -EINVAL;

	*pkey = QLNXR_ROCE_PKEY_DEFAULT;

	QL_DPRINT12(ha, "exit\n");
	return 0;
}