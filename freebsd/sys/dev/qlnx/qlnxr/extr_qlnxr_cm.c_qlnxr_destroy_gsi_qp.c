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
struct qlnxr_dev {int /*<<< orphan*/  ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ ,char*,...) ; 
 int qlnxr_ll2_stop (struct qlnxr_dev*) ; 

int
qlnxr_destroy_gsi_qp(struct qlnxr_dev *dev)
{
	int rc = 0;

	QL_DPRINT12(dev->ha, "enter\n");

	rc = qlnxr_ll2_stop(dev);

	QL_DPRINT12(dev->ha, "exit rc = %d\n", rc);
	return (rc);
}