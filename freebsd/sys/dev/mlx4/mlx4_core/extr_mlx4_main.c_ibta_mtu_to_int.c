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
typedef  enum ibta_mtu { ____Placeholder_ibta_mtu } ibta_mtu ;

/* Variables and functions */
#define  IB_MTU_1024 132 
#define  IB_MTU_2048 131 
#define  IB_MTU_256 130 
#define  IB_MTU_4096 129 
#define  IB_MTU_512 128 

__attribute__((used)) static inline int ibta_mtu_to_int(enum ibta_mtu mtu)
{
	switch (mtu) {
	case IB_MTU_256:  return  256;
	case IB_MTU_512:  return  512;
	case IB_MTU_1024: return 1024;
	case IB_MTU_2048: return 2048;
	case IB_MTU_4096: return 4096;
	default: return -1;
	}
}