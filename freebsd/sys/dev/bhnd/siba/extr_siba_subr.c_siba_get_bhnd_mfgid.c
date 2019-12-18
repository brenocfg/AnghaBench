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
 int BHND_MFGID_BCM ; 
 int BHND_MFGID_INVALID ; 
#define  OCP_VENDOR_BCM 128 

uint16_t
siba_get_bhnd_mfgid(uint16_t ocp_vendor)
{
	switch (ocp_vendor) {
	case OCP_VENDOR_BCM:
		return (BHND_MFGID_BCM);
	default:
		return (BHND_MFGID_INVALID);
	}
}