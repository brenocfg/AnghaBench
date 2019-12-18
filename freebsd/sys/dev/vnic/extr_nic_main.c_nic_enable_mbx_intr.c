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
typedef  int /*<<< orphan*/  uint64_t ;
struct nicpf {int dummy; } ;

/* Variables and functions */
 scalar_t__ NIC_PF_MAILBOX_ENA_W1S ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,scalar_t__,unsigned long) ; 

__attribute__((used)) static void
nic_enable_mbx_intr(struct nicpf *nic)
{

	/* Enable mailbox interrupt for all 128 VFs */
	nic_reg_write(nic, NIC_PF_MAILBOX_ENA_W1S, ~0UL);
	nic_reg_write(nic, NIC_PF_MAILBOX_ENA_W1S + sizeof(uint64_t), ~0UL);
}