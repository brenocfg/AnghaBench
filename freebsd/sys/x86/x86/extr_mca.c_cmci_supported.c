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

/* Variables and functions */
 scalar_t__ CPU_VENDOR_INTEL ; 
 int MCG_CAP_CMCI_P ; 
 scalar_t__ cpu_vendor_id ; 

__attribute__((used)) static inline bool
cmci_supported(uint64_t mcg_cap)
{
	/*
	 * MCG_CAP_CMCI_P bit is reserved in AMD documentation.  Until
	 * it is defined, do not use it to check for CMCI support.
	 */
	if (cpu_vendor_id != CPU_VENDOR_INTEL)
		return (false);
	return ((mcg_cap & MCG_CAP_CMCI_P) != 0);
}