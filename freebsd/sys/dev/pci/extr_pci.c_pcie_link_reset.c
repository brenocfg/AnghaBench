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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int PCIEM_LINK_CTL_LINK_DIS ; 
 int PCIEM_LINK_CTL_RETRAIN_LINK ; 
 int PCIEM_LINK_STA_TRAINING ; 
 scalar_t__ PCIER_LINK_CTL ; 
 scalar_t__ PCIER_LINK_STA ; 
 int /*<<< orphan*/  mstosbt (int) ; 
 int /*<<< orphan*/  pause_sbt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

int
pcie_link_reset(device_t port, int pcie_location)
{
	uint16_t v;

	v = pci_read_config(port, pcie_location + PCIER_LINK_CTL, 2);
	v |= PCIEM_LINK_CTL_LINK_DIS;
	pci_write_config(port, pcie_location + PCIER_LINK_CTL, v, 2);
	pause_sbt("pcier1", mstosbt(20), 0, 0);
	v &= ~PCIEM_LINK_CTL_LINK_DIS;
	v |= PCIEM_LINK_CTL_RETRAIN_LINK;
	pci_write_config(port, pcie_location + PCIER_LINK_CTL, v, 2);
	pause_sbt("pcier2", mstosbt(100), 0, 0); /* 100 ms */
	v = pci_read_config(port, pcie_location + PCIER_LINK_STA, 2);
	return ((v & PCIEM_LINK_STA_TRAINING) != 0 ? ETIMEDOUT : 0);
}