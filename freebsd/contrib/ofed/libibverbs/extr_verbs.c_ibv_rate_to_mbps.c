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
#define  IBV_RATE_100_GBPS 148 
#define  IBV_RATE_10_GBPS 147 
#define  IBV_RATE_112_GBPS 146 
#define  IBV_RATE_120_GBPS 145 
#define  IBV_RATE_14_GBPS 144 
#define  IBV_RATE_168_GBPS 143 
#define  IBV_RATE_200_GBPS 142 
#define  IBV_RATE_20_GBPS 141 
#define  IBV_RATE_25_GBPS 140 
#define  IBV_RATE_28_GBPS 139 
#define  IBV_RATE_2_5_GBPS 138 
#define  IBV_RATE_300_GBPS 137 
#define  IBV_RATE_30_GBPS 136 
#define  IBV_RATE_400_GBPS 135 
#define  IBV_RATE_40_GBPS 134 
#define  IBV_RATE_50_GBPS 133 
#define  IBV_RATE_56_GBPS 132 
#define  IBV_RATE_5_GBPS 131 
#define  IBV_RATE_600_GBPS 130 
#define  IBV_RATE_60_GBPS 129 
#define  IBV_RATE_80_GBPS 128 

int  __attribute__((const)) ibv_rate_to_mbps(enum ibv_rate rate)
{
	switch (rate) {
	case IBV_RATE_2_5_GBPS: return 2500;
	case IBV_RATE_5_GBPS:   return 5000;
	case IBV_RATE_10_GBPS:  return 10000;
	case IBV_RATE_20_GBPS:  return 20000;
	case IBV_RATE_30_GBPS:  return 30000;
	case IBV_RATE_40_GBPS:  return 40000;
	case IBV_RATE_60_GBPS:  return 60000;
	case IBV_RATE_80_GBPS:  return 80000;
	case IBV_RATE_120_GBPS: return 120000;
	case IBV_RATE_14_GBPS:  return 14062;
	case IBV_RATE_56_GBPS:  return 56250;
	case IBV_RATE_112_GBPS: return 112500;
	case IBV_RATE_168_GBPS: return 168750;
	case IBV_RATE_25_GBPS:  return 25781;
	case IBV_RATE_100_GBPS: return 103125;
	case IBV_RATE_200_GBPS: return 206250;
	case IBV_RATE_300_GBPS: return 309375;
	case IBV_RATE_28_GBPS:  return 28125;
	case IBV_RATE_50_GBPS:  return 53125;
	case IBV_RATE_400_GBPS: return 425000;
	case IBV_RATE_600_GBPS: return 637500;
	default:               return -1;
	}
}