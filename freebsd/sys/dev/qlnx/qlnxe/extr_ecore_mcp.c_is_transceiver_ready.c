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
 int ETH_TRANSCEIVER_STATE_PRESENT ; 
 int ETH_TRANSCEIVER_STATE_UPDATING ; 
 int ETH_TRANSCEIVER_TYPE_NONE ; 

__attribute__((used)) static int is_transceiver_ready(u32 transceiver_state, u32 transceiver_type)
{

	if ((transceiver_state & ETH_TRANSCEIVER_STATE_PRESENT) &&
	    ((transceiver_state & ETH_TRANSCEIVER_STATE_UPDATING) == 0x0) &&
	    (transceiver_type != ETH_TRANSCEIVER_TYPE_NONE)) {
		return 1;
	}

	return 0;
}