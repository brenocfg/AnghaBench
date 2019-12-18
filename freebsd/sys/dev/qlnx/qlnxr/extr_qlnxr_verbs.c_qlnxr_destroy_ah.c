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
struct qlnxr_ah {int dummy; } ;
struct ib_ah {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 
 struct qlnxr_ah* get_qlnxr_ah (struct ib_ah*) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_ah*) ; 

int
qlnxr_destroy_ah(struct ib_ah *ibah)
{
	struct qlnxr_dev *dev;
	qlnx_host_t     *ha;
	struct qlnxr_ah *ah = get_qlnxr_ah(ibah);
	
	dev = get_qlnxr_dev((ibah->device));
	ha = dev->ha;

	QL_DPRINT12(ha, "in destroy_ah\n");

	kfree(ah);
	return 0;
}