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
typedef  int uint16_t ;
struct nicpf {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  NIC_PF_SW_SYNC_RX ; 
 int /*<<< orphan*/  NIC_PF_SW_SYNC_RX_DONE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int nic_reg_read (struct nicpf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nic_rcv_queue_sw_sync(struct nicpf *nic)
{
	uint16_t timeout = ~0x00;

	nic_reg_write(nic, NIC_PF_SW_SYNC_RX, 0x01);
	/* Wait till sync cycle is finished */
	while (timeout) {
		if (nic_reg_read(nic, NIC_PF_SW_SYNC_RX_DONE) & 0x1)
			break;
		timeout--;
	}
	nic_reg_write(nic, NIC_PF_SW_SYNC_RX, 0x00);
	if (!timeout) {
		device_printf(nic->dev, "Receive queue software sync failed\n");
		return (ETIMEDOUT);
	}
	return (0);
}