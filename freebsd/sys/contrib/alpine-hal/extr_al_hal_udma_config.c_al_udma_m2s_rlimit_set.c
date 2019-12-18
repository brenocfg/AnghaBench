#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct al_udma_m2s_rlimit_mode {scalar_t__ pkt_mode_en; int short_cycle_sz; int token_init_val; } ;
struct al_udma {TYPE_3__* udma_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl_token; int /*<<< orphan*/  gen_cfg; } ;
struct TYPE_5__ {TYPE_1__ m2s_rate_limiter; } ;
struct TYPE_6__ {TYPE_2__ m2s; } ;

/* Variables and functions */
 scalar_t__ AL_TRUE ; 
 int UDMA_M2S_RATE_LIMITER_CTRL_TOKEN_RST_MASK ; 
 int UDMA_M2S_RATE_LIMITER_GEN_CFG_PKT_MODE_EN ; 
 int UDMA_M2S_RATE_LIMITER_GEN_CFG_SHORT_CYCLE_SIZE_MASK ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_udma_m2s_rlimit_set(struct al_udma *udma,
					struct al_udma_m2s_rlimit_mode *mode)
{
	uint32_t reg = al_reg_read32(
				&udma->udma_regs->m2s.m2s_rate_limiter.gen_cfg);

	if (mode->pkt_mode_en == AL_TRUE)
		reg |= UDMA_M2S_RATE_LIMITER_GEN_CFG_PKT_MODE_EN;
	else
		reg &= ~UDMA_M2S_RATE_LIMITER_GEN_CFG_PKT_MODE_EN;
	reg &= ~UDMA_M2S_RATE_LIMITER_GEN_CFG_SHORT_CYCLE_SIZE_MASK;
	reg |= mode->short_cycle_sz &
	    UDMA_M2S_RATE_LIMITER_GEN_CFG_SHORT_CYCLE_SIZE_MASK;
	al_reg_write32(&udma->udma_regs->m2s.m2s_rate_limiter.gen_cfg, reg);

	reg = al_reg_read32(&udma->udma_regs->m2s.m2s_rate_limiter.ctrl_token);
	reg &= ~UDMA_M2S_RATE_LIMITER_CTRL_TOKEN_RST_MASK;
	reg |= mode->token_init_val &
			UDMA_M2S_RATE_LIMITER_CTRL_TOKEN_RST_MASK;
	al_reg_write32(&udma->udma_regs->m2s.m2s_rate_limiter.ctrl_token, reg);

	return 0;
}