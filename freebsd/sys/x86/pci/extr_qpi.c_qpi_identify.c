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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int) ; 
 int CPUID_TO_FAMILY (int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_VENDOR_INTEL ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  cpu_id ; 
 scalar_t__ cpu_vendor_id ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pci_cfgregopen () ; 

__attribute__((used)) static void
qpi_identify(driver_t *driver, device_t parent)
{
	int do_qpi;

	/* Check CPUID to ensure this is an i7 CPU of some sort. */
	if (cpu_vendor_id != CPU_VENDOR_INTEL ||
	    CPUID_TO_FAMILY(cpu_id) != 0x6)
		return;

	/* Only discover buses with configuration devices if allowed by user */
	do_qpi = 0;
	TUNABLE_INT_FETCH("hw.attach_intel_csr_pci", &do_qpi);
	if (!do_qpi)
		return;

	/* PCI config register access is required. */
	if (pci_cfgregopen() == 0)
		return;

	/* Add a qpi bus device. */
	if (BUS_ADD_CHILD(parent, 20, "qpi", -1) == NULL)
		panic("Failed to add qpi bus");
}