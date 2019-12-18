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
typedef  int UINT8 ;

/* Variables and functions */
#define  IVRS_TYPE_HARDWARE_EFR 130 
#define  IVRS_TYPE_HARDWARE_LEGACY 129 
#define  IVRS_TYPE_HARDWARE_MIXED 128 

__attribute__((used)) static bool
ivrs_is_ivhd(UINT8 type)
{

	switch(type) {
	case IVRS_TYPE_HARDWARE_LEGACY:
	case IVRS_TYPE_HARDWARE_EFR:
	case IVRS_TYPE_HARDWARE_MIXED:
		return (true);

	default:
		return (false);
	}
}