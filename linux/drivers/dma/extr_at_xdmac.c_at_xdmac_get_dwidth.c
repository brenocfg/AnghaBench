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
typedef  int u32 ;

/* Variables and functions */
 int AT_XDMAC_CC_DWIDTH_MASK ; 
 int AT_XDMAC_CC_DWIDTH_OFFSET ; 

__attribute__((used)) static inline u8 at_xdmac_get_dwidth(u32 cfg)
{
	return (cfg & AT_XDMAC_CC_DWIDTH_MASK) >> AT_XDMAC_CC_DWIDTH_OFFSET;
}