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
typedef  int uint32_t ;
struct udma_rlimit_common {int /*<<< orphan*/  mask; int /*<<< orphan*/  cfg_token_size_2; int /*<<< orphan*/  cfg_token_size_1; int /*<<< orphan*/  cfg_cycle; int /*<<< orphan*/  cfg_1s; } ;
struct al_udma_m2s_rlimit_cfg {int max_burst_sz; int long_cycle_sz; int long_cycle; int short_cycle; int mask; } ;

/* Variables and functions */
 int UDMA_M2S_STREAM_RATE_LIMITER_CFG_1S_EN ; 
 int UDMA_M2S_STREAM_RATE_LIMITER_CFG_1S_MAX_BURST_SIZE_MASK ; 
 int UDMA_M2S_STREAM_RATE_LIMITER_CFG_1S_PAUSE ; 
 int UDMA_M2S_STREAM_RATE_LIMITER_CFG_CYCLE_LONG_CYCLE_SIZE_MASK ; 
 int UDMA_M2S_STREAM_RATE_LIMITER_CFG_TOKEN_SIZE_1_LONG_CYCLE_MASK ; 
 int UDMA_M2S_STREAM_RATE_LIMITER_CFG_TOKEN_SIZE_2_SHORT_CYCLE_MASK ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int al_udma_common_rlimit_set(struct udma_rlimit_common *regs,
					  struct al_udma_m2s_rlimit_cfg *conf)
{
	uint32_t reg = al_reg_read32(&regs->cfg_1s);
	/* mask max burst size, and enable/pause control bits */
	reg &= ~UDMA_M2S_STREAM_RATE_LIMITER_CFG_1S_MAX_BURST_SIZE_MASK;
	reg &= ~UDMA_M2S_STREAM_RATE_LIMITER_CFG_1S_EN;
	reg &= ~UDMA_M2S_STREAM_RATE_LIMITER_CFG_1S_PAUSE;
	reg |= conf->max_burst_sz &
		UDMA_M2S_STREAM_RATE_LIMITER_CFG_1S_MAX_BURST_SIZE_MASK;
	al_reg_write32(&regs->cfg_1s, reg);

	reg = al_reg_read32(&regs->cfg_cycle);
	reg &= ~UDMA_M2S_STREAM_RATE_LIMITER_CFG_CYCLE_LONG_CYCLE_SIZE_MASK;
	reg |= conf->long_cycle_sz &
		UDMA_M2S_STREAM_RATE_LIMITER_CFG_CYCLE_LONG_CYCLE_SIZE_MASK;
	al_reg_write32(&regs->cfg_cycle, reg);

	reg = al_reg_read32(&regs->cfg_token_size_1);
	reg &= ~UDMA_M2S_STREAM_RATE_LIMITER_CFG_TOKEN_SIZE_1_LONG_CYCLE_MASK;
	reg |= conf->long_cycle &
		UDMA_M2S_STREAM_RATE_LIMITER_CFG_TOKEN_SIZE_1_LONG_CYCLE_MASK;
	al_reg_write32(&regs->cfg_token_size_1, reg);

	reg = al_reg_read32(&regs->cfg_token_size_2);
	reg &= ~UDMA_M2S_STREAM_RATE_LIMITER_CFG_TOKEN_SIZE_2_SHORT_CYCLE_MASK;
	reg |= conf->short_cycle &
		UDMA_M2S_STREAM_RATE_LIMITER_CFG_TOKEN_SIZE_2_SHORT_CYCLE_MASK;
	al_reg_write32(&regs->cfg_token_size_2, reg);

	reg = al_reg_read32(&regs->mask);
	reg &= ~0xf;		/* only bits 0-3 defined */
	reg |= conf->mask & 0xf;
	al_reg_write32(&regs->mask, reg);

	return 0;
}