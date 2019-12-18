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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NAE_FREE_IN_FIFO_CFG ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_deflate_frin_fifo_carving(uint64_t nae_base, int total_num_ports)
{
	const int minimum_size = 8;
	uint32_t value;
	int intf, start;

	for (intf = 0; intf < total_num_ports; intf++) {
		start = minimum_size * intf;
		value = (minimum_size << 20) | (start << 8) | (intf);
		nlm_write_nae_reg(nae_base, NAE_FREE_IN_FIFO_CFG, value);
	}
}