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
typedef  int u8 ;

/* Variables and functions */
#define  IB_RATE_10_GBPS 130 
#define  IB_RATE_2_5_GBPS 129 
#define  IB_RATE_5_GBPS 128 
 int MTHCA_RATE_TAVOR_1X ; 
 int MTHCA_RATE_TAVOR_1X_DDR ; 
 int MTHCA_RATE_TAVOR_4X ; 
 int MTHCA_RATE_TAVOR_FULL ; 

__attribute__((used)) static u8 ib_rate_to_tavor(u8 static_rate)
{
	switch (static_rate) {
	case IB_RATE_2_5_GBPS: return MTHCA_RATE_TAVOR_1X;
	case IB_RATE_5_GBPS:   return MTHCA_RATE_TAVOR_1X_DDR;
	case IB_RATE_10_GBPS:  return MTHCA_RATE_TAVOR_4X;
	default:	       return MTHCA_RATE_TAVOR_FULL;
	}
}