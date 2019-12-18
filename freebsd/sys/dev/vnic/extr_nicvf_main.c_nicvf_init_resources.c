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
struct TYPE_2__ {int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ msg; } ;
struct nicvf {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_CFG_DONE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int nicvf_config_data_transfer (struct nicvf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_qset_config (struct nicvf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_write_to_mbx (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static int
nicvf_init_resources(struct nicvf *nic)
{
	int err;
	union nic_mbx mbx = {};

	mbx.msg.msg = NIC_MBOX_MSG_CFG_DONE;

	/* Enable Qset */
	nicvf_qset_config(nic, TRUE);

	/* Initialize queues and HW for data transfer */
	err = nicvf_config_data_transfer(nic, TRUE);
	if (err) {
		device_printf(nic->dev,
		    "Failed to alloc/config VF's QSet resources\n");
		return (err);
	}

	/* Send VF config done msg to PF */
	nicvf_write_to_mbx(nic, &mbx);

	return (0);
}