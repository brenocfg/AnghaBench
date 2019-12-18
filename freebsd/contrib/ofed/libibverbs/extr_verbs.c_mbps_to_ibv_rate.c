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
 int IBV_RATE_100_GBPS ; 
 int IBV_RATE_10_GBPS ; 
 int IBV_RATE_112_GBPS ; 
 int IBV_RATE_120_GBPS ; 
 int IBV_RATE_14_GBPS ; 
 int IBV_RATE_168_GBPS ; 
 int IBV_RATE_200_GBPS ; 
 int IBV_RATE_20_GBPS ; 
 int IBV_RATE_25_GBPS ; 
 int IBV_RATE_28_GBPS ; 
 int IBV_RATE_2_5_GBPS ; 
 int IBV_RATE_300_GBPS ; 
 int IBV_RATE_30_GBPS ; 
 int IBV_RATE_400_GBPS ; 
 int IBV_RATE_40_GBPS ; 
 int IBV_RATE_50_GBPS ; 
 int IBV_RATE_56_GBPS ; 
 int IBV_RATE_5_GBPS ; 
 int IBV_RATE_600_GBPS ; 
 int IBV_RATE_60_GBPS ; 
 int IBV_RATE_80_GBPS ; 
 int IBV_RATE_MAX ; 

enum ibv_rate __attribute__((const)) mbps_to_ibv_rate(int mbps)
{
	switch (mbps) {
	case 2500:   return IBV_RATE_2_5_GBPS;
	case 5000:   return IBV_RATE_5_GBPS;
	case 10000:  return IBV_RATE_10_GBPS;
	case 20000:  return IBV_RATE_20_GBPS;
	case 30000:  return IBV_RATE_30_GBPS;
	case 40000:  return IBV_RATE_40_GBPS;
	case 60000:  return IBV_RATE_60_GBPS;
	case 80000:  return IBV_RATE_80_GBPS;
	case 120000: return IBV_RATE_120_GBPS;
	case 14062:  return IBV_RATE_14_GBPS;
	case 56250:  return IBV_RATE_56_GBPS;
	case 112500: return IBV_RATE_112_GBPS;
	case 168750: return IBV_RATE_168_GBPS;
	case 25781:  return IBV_RATE_25_GBPS;
	case 103125: return IBV_RATE_100_GBPS;
	case 206250: return IBV_RATE_200_GBPS;
	case 309375: return IBV_RATE_300_GBPS;
	case 28125:  return IBV_RATE_28_GBPS;
	case 53125:  return IBV_RATE_50_GBPS;
	case 425000: return IBV_RATE_400_GBPS;
	case 637500: return IBV_RATE_600_GBPS;
	default:     return IBV_RATE_MAX;
	}
}