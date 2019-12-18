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
struct nicpf {int dummy; } ;

/* Variables and functions */
 scalar_t__ NIC_PF_MAILBOX_INT ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,scalar_t__,unsigned long) ; 

__attribute__((used)) static void
nic_clear_mbx_intr(struct nicpf *nic, int vf, int mbx_reg)
{

	nic_reg_write(nic, NIC_PF_MAILBOX_INT + (mbx_reg << 3), (1UL << vf));
}