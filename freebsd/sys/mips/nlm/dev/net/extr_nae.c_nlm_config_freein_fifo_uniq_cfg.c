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
 int NAE_CACHELINE_SIZE ; 
 int /*<<< orphan*/  NAE_FREEIN_FIFO_UNIQ_SZ_CFG ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_config_freein_fifo_uniq_cfg(uint64_t nae_base, int port,
    int nblock_free_desc)
{
	uint32_t val;
	int size_in_clines;

	size_in_clines = (nblock_free_desc / NAE_CACHELINE_SIZE);
	val = (size_in_clines << 8) | (port & 0x1f);
	nlm_write_nae_reg(nae_base, NAE_FREEIN_FIFO_UNIQ_SZ_CFG, val);
}