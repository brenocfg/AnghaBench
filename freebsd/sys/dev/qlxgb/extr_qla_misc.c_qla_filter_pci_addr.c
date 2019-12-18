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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int Q8_INVALID_ADDRESS ; 

__attribute__((used)) static uint32_t
qla_filter_pci_addr(qla_host_t *ha, uint32_t addr)
{
	if ((addr == Q8_INVALID_ADDRESS) ||
		(addr == 0x00112040) ||
		(addr == 0x00112048) ||
		((addr & 0xFFFF0FFF) == 0x001100C4) ||
		((addr & 0xFFFF0FFF) == 0x001100C8) ||
		((addr & 0x0FF00000) == 0x00200000) ||
		(addr == 0x022021FC) ||
		(addr == 0x0330001C) ||
		(addr == 0x03300024) ||
		(addr == 0x033000A8) ||
		(addr == 0x033000C8) ||
		(addr == 0x033000BC) ||
		((addr & 0x0FF00000) == 0x03A00000) ||
		(addr == 0x03B0001C))
		return (Q8_INVALID_ADDRESS);
	else
		return (addr); 
}