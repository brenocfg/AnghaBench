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
 int /*<<< orphan*/  NAE_RX_FREE_FIFO_POP ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_nae_flush_free_fifo(uint64_t nae_base, int nblocks)
{
	uint32_t data, fifo_mask;

	fifo_mask = (1 << (4 * nblocks)) - 1;

	nlm_write_nae_reg(nae_base, NAE_RX_FREE_FIFO_POP, fifo_mask);
	do {
		data = nlm_read_nae_reg(nae_base, NAE_RX_FREE_FIFO_POP);
	} while (data != fifo_mask);

	nlm_write_nae_reg(nae_base, NAE_RX_FREE_FIFO_POP, 0);
}