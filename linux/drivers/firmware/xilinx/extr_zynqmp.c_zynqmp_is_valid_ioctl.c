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
typedef  int u32 ;

/* Variables and functions */
#define  IOCTL_GET_PLL_FRAC_DATA 131 
#define  IOCTL_GET_PLL_FRAC_MODE 130 
#define  IOCTL_SET_PLL_FRAC_DATA 129 
#define  IOCTL_SET_PLL_FRAC_MODE 128 

__attribute__((used)) static inline int zynqmp_is_valid_ioctl(u32 ioctl_id)
{
	switch (ioctl_id) {
	case IOCTL_SET_PLL_FRAC_MODE:
	case IOCTL_GET_PLL_FRAC_MODE:
	case IOCTL_SET_PLL_FRAC_DATA:
	case IOCTL_GET_PLL_FRAC_DATA:
		return 1;
	default:
		return 0;
	}
}