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
 int MTHCA_RATE_MEMFREE_EIGHTH ; 
 int MTHCA_RATE_MEMFREE_FULL ; 
 int MTHCA_RATE_MEMFREE_HALF ; 
 int MTHCA_RATE_MEMFREE_QUARTER ; 

__attribute__((used)) static u8 ib_rate_to_memfree(u8 req_rate, u8 cur_rate)
{
	if (cur_rate <= req_rate)
		return 0;

	/*
	 * Inter-packet delay (IPD) to get from rate X down to a rate
	 * no more than Y is (X - 1) / Y.
	 */
	switch ((cur_rate - 1) / req_rate) {
	case 0:	 return MTHCA_RATE_MEMFREE_FULL;
	case 1:	 return MTHCA_RATE_MEMFREE_HALF;
	case 2:	 /* fall through */
	case 3:	 return MTHCA_RATE_MEMFREE_QUARTER;
	default: return MTHCA_RATE_MEMFREE_EIGHTH;
	}
}