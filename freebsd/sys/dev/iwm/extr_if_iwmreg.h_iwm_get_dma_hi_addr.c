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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int bus_addr_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */

__attribute__((used)) static inline uint8_t iwm_get_dma_hi_addr(bus_addr_t addr)
{
	return (sizeof(addr) > sizeof(uint32_t) ? (addr >> 16) >> 16 : 0) & 0xF;
}