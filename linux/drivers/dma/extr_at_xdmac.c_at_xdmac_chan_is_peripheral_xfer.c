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
 int AT_XDMAC_CC_TYPE_PER_TRAN ; 

__attribute__((used)) static inline bool at_xdmac_chan_is_peripheral_xfer(u32 cfg)
{
	return cfg & AT_XDMAC_CC_TYPE_PER_TRAN;
}