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
typedef  int uint64_t ;
typedef  int pci_addr_t ;

/* Variables and functions */
 int PCIM_BIOS_ADDR_MASK ; 

__attribute__((used)) static pci_addr_t
pci_rombase(uint64_t mapreg)
{

	return (mapreg & PCIM_BIOS_ADDR_MASK);
}