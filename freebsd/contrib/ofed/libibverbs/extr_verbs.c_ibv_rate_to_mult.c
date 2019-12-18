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
typedef  enum ibv_rate { ____Placeholder_ibv_rate } ibv_rate ;

/* Variables and functions */
#define  IBV_RATE_10_GBPS 140 
#define  IBV_RATE_120_GBPS 139 
#define  IBV_RATE_20_GBPS 138 
#define  IBV_RATE_28_GBPS 137 
#define  IBV_RATE_2_5_GBPS 136 
#define  IBV_RATE_30_GBPS 135 
#define  IBV_RATE_400_GBPS 134 
#define  IBV_RATE_40_GBPS 133 
#define  IBV_RATE_50_GBPS 132 
#define  IBV_RATE_5_GBPS 131 
#define  IBV_RATE_600_GBPS 130 
#define  IBV_RATE_60_GBPS 129 
#define  IBV_RATE_80_GBPS 128 

int __attribute__((const)) ibv_rate_to_mult(enum ibv_rate rate)
{
	switch (rate) {
	case IBV_RATE_2_5_GBPS: return  1;
	case IBV_RATE_5_GBPS:   return  2;
	case IBV_RATE_10_GBPS:  return  4;
	case IBV_RATE_20_GBPS:  return  8;
	case IBV_RATE_30_GBPS:  return 12;
	case IBV_RATE_40_GBPS:  return 16;
	case IBV_RATE_60_GBPS:  return 24;
	case IBV_RATE_80_GBPS:  return 32;
	case IBV_RATE_120_GBPS: return 48;
	case IBV_RATE_28_GBPS:  return 11;
	case IBV_RATE_50_GBPS:  return 20;
	case IBV_RATE_400_GBPS: return 160;
	case IBV_RATE_600_GBPS: return 240;
	default:           return -1;
	}
}