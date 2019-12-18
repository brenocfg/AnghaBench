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
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_ah_attr {int dummy; } ;
struct ib_ah {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 

int
qlnxr_query_ah(struct ib_ah *ibah, struct ib_ah_attr *attr)
{
	struct qlnxr_dev *dev;
	qlnx_host_t     *ha;

	dev = get_qlnxr_dev((ibah->device));
	ha = dev->ha;
	QL_DPRINT12(ha, "Query AH not supported\n");
	return -EINVAL;
}