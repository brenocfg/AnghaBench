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

/* Variables and functions */
#define  BHND_MFGID_ARM 130 
#define  BHND_MFGID_BCM 129 
#define  BHND_MFGID_MIPS 128 

const char *
bhnd_vendor_name(uint16_t vendor)
{
	switch (vendor) {
	case BHND_MFGID_ARM:
		return "ARM";
	case BHND_MFGID_BCM:
		return "Broadcom";
	case BHND_MFGID_MIPS:
		return "MIPS";
	default:
		return "unknown";
	}
}