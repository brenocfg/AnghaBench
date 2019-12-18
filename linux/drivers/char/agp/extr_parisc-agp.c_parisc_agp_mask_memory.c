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
struct agp_bridge_data {int dummy; } ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 unsigned long SBA_PDIR_VALID_BIT ; 

__attribute__((used)) static unsigned long
parisc_agp_mask_memory(struct agp_bridge_data *bridge, dma_addr_t addr,
		       int type)
{
	return SBA_PDIR_VALID_BIT | addr;
}