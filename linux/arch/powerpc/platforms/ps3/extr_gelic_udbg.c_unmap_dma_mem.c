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
typedef  int u64 ;
typedef  int s64 ;

/* Variables and functions */
 int lv1_free_device_dma_region (int,int,int) ; 
 int lv1_unmap_device_dma_region (int,int,int,size_t) ; 

__attribute__((used)) static int unmap_dma_mem(int bus_id, int dev_id, u64 bus_addr, size_t len)
{
	s64 result;
	u64 real_bus_addr;

	real_bus_addr = bus_addr & ~0xfff;
	len += bus_addr - real_bus_addr;
	len = (len + 0xfff) & ~0xfff;

	result = lv1_unmap_device_dma_region(bus_id, dev_id, real_bus_addr,
					     len);
	if (result)
		return result;

	return lv1_free_device_dma_region(bus_id, dev_id, real_bus_addr);
}