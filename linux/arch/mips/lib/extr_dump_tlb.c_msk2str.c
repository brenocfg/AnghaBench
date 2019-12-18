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

/* Variables and functions */
#define  PM_128K 144 
#define  PM_16K 143 
#define  PM_16M 142 
#define  PM_1G 141 
#define  PM_1M 140 
#define  PM_256K 139 
#define  PM_256M 138 
#define  PM_2M 137 
#define  PM_32K 136 
#define  PM_32M 135 
#define  PM_4K 134 
#define  PM_4M 133 
#define  PM_512K 132 
#define  PM_64K 131 
#define  PM_64M 130 
#define  PM_8K 129 
#define  PM_8M 128 

__attribute__((used)) static inline const char *msk2str(unsigned int mask)
{
	switch (mask) {
	case PM_4K:	return "4kb";
	case PM_16K:	return "16kb";
	case PM_64K:	return "64kb";
	case PM_256K:	return "256kb";
#ifdef CONFIG_CPU_CAVIUM_OCTEON
	case PM_8K:	return "8kb";
	case PM_32K:	return "32kb";
	case PM_128K:	return "128kb";
	case PM_512K:	return "512kb";
	case PM_2M:	return "2Mb";
	case PM_8M:	return "8Mb";
	case PM_32M:	return "32Mb";
#endif
#ifndef CONFIG_CPU_VR41XX
	case PM_1M:	return "1Mb";
	case PM_4M:	return "4Mb";
	case PM_16M:	return "16Mb";
	case PM_64M:	return "64Mb";
	case PM_256M:	return "256Mb";
	case PM_1G:	return "1Gb";
#endif
	}
	return "";
}