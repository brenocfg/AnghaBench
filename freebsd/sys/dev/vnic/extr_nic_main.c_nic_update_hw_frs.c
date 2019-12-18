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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int maxlen; } ;
struct nicpf {TYPE_1__ pkind; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ETHER_HDR_LEN ; 
 int NIC_HW_MAX_FRS ; 
 int NIC_HW_MIN_FRS ; 
 int /*<<< orphan*/  NIC_PF_PKIND_0_15_CFG ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nic_update_hw_frs(struct nicpf *nic, int new_frs, int vf)
{

	if ((new_frs > NIC_HW_MAX_FRS) || (new_frs < NIC_HW_MIN_FRS)) {
		device_printf(nic->dev,
		    "Invalid MTU setting from VF%d rejected, "
		    "should be between %d and %d\n",
		    vf, NIC_HW_MIN_FRS, NIC_HW_MAX_FRS);
		return (EINVAL);
	}
	new_frs += ETHER_HDR_LEN;
	if (new_frs <= nic->pkind.maxlen)
		return (0);

	nic->pkind.maxlen = new_frs;
	nic_reg_write(nic, NIC_PF_PKIND_0_15_CFG, *(uint64_t *)&nic->pkind);
	return (0);
}