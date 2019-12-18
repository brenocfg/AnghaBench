#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ if_rxd_info_t ;
typedef  TYPE_1__* if_rxd_info_pad_t ;
struct TYPE_2__ {scalar_t__* rxd_val; } ;

/* Variables and functions */
 int RXD_INFO_SIZE ; 
 int RXD_LOOP_BOUND ; 

__attribute__((used)) static inline void
rxd_info_zero(if_rxd_info_t ri)
{
	if_rxd_info_pad_t ri_pad;
	int i;

	ri_pad = (if_rxd_info_pad_t)ri;
	for (i = 0; i < RXD_LOOP_BOUND; i += 4) {
		ri_pad->rxd_val[i] = 0;
		ri_pad->rxd_val[i+1] = 0;
		ri_pad->rxd_val[i+2] = 0;
		ri_pad->rxd_val[i+3] = 0;
	}
#ifdef __LP64__
	ri_pad->rxd_val[RXD_INFO_SIZE-1] = 0;
#endif
}