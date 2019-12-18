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
typedef  union nic_mbx {int dummy; } nic_mbx ;
typedef  int /*<<< orphan*/  uint64_t ;
struct nicpf {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ bus_space_handle_t ;

/* Variables and functions */
 scalar_t__ nic_get_mbx_addr (int) ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pass1_silicon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nic_send_msg_to_vf(struct nicpf *nic, int vf, union nic_mbx *mbx)
{
	bus_space_handle_t mbx_addr = nic_get_mbx_addr(vf);
	uint64_t *msg = (uint64_t *)mbx;

	/*
	 * In first revision HW, mbox interrupt is triggerred
	 * when PF writes to MBOX(1), in next revisions when
	 * PF writes to MBOX(0)
	 */
	if (pass1_silicon(nic->dev)) {
		nic_reg_write(nic, mbx_addr + 0, msg[0]);
		nic_reg_write(nic, mbx_addr + 8, msg[1]);
	} else {
		nic_reg_write(nic, mbx_addr + 8, msg[1]);
		nic_reg_write(nic, mbx_addr + 0, msg[0]);
	}
}