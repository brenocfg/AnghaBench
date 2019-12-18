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
typedef  int /*<<< orphan*/  dbg ;

/* Variables and functions */
 int /*<<< orphan*/  GELIC_BUS_ID ; 
 int /*<<< orphan*/  GELIC_DEVICE_ID ; 
 scalar_t__ bus_addr ; 
 int /*<<< orphan*/  lv1_close_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_dma_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void gelic_debug_shutdown(void)
{
	if (bus_addr)
		unmap_dma_mem(GELIC_BUS_ID, GELIC_DEVICE_ID,
			      bus_addr, sizeof(dbg));
	lv1_close_device(GELIC_BUS_ID, GELIC_DEVICE_ID);
}