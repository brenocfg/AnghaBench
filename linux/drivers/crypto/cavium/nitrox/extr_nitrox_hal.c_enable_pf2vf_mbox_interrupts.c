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
typedef  unsigned long long u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 unsigned long long NPS_PKT_MBOX_INT_HI_ENA_W1S ; 
 unsigned long long NPS_PKT_MBOX_INT_LO_ENA_W1S ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,unsigned long long,unsigned long long) ; 

void enable_pf2vf_mbox_interrupts(struct nitrox_device *ndev)
{
	u64 value = ~0ULL;
	u64 reg_addr;

	/* Mailbox interrupt low enable set register */
	reg_addr = NPS_PKT_MBOX_INT_LO_ENA_W1S;
	nitrox_write_csr(ndev, reg_addr, value);

	/* Mailbox interrupt high enable set register */
	reg_addr = NPS_PKT_MBOX_INT_HI_ENA_W1S;
	nitrox_write_csr(ndev, reg_addr, value);
}