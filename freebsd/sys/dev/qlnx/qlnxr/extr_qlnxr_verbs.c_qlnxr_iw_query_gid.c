#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union ib_gid {int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  u8 ;
struct qlnxr_dev {TYPE_1__* ha; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  primary_mac; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_1__*,char*) ; 
 struct qlnxr_dev* get_qlnxr_dev (struct ib_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
qlnxr_iw_query_gid(struct ib_device *ibdev, u8 port, int index,
	union ib_gid *sgid)
{
	struct qlnxr_dev	*dev;
	qlnx_host_t		*ha;

	dev = get_qlnxr_dev(ibdev);
	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	memset(sgid->raw, 0, sizeof(sgid->raw));

	memcpy(sgid->raw, dev->ha->primary_mac, sizeof (dev->ha->primary_mac));

	QL_DPRINT12(ha, "exit\n");

	return 0;
}