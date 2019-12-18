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
typedef  int /*<<< orphan*/  uint32_t ;
struct udma_rlimit_common {int /*<<< orphan*/  sw_ctrl; int /*<<< orphan*/  cfg_1s; } ;
typedef  enum al_udma_m2s_rlimit_action { ____Placeholder_al_udma_m2s_rlimit_action } al_udma_m2s_rlimit_action ;

/* Variables and functions */
#define  AL_UDMA_STRM_RLIMIT_ENABLE 130 
#define  AL_UDMA_STRM_RLIMIT_PAUSE 129 
#define  AL_UDMA_STRM_RLIMIT_RESET 128 
 int EINVAL ; 
 int /*<<< orphan*/  UDMA_M2S_STREAM_RATE_LIMITER_CFG_1S_EN ; 
 int /*<<< orphan*/  UDMA_M2S_STREAM_RATE_LIMITER_CFG_1S_PAUSE ; 
 int /*<<< orphan*/  UDMA_M2S_STREAM_RATE_LIMITER_SW_CTRL_RST_TOKEN_CNT ; 
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int al_udma_common_rlimit_act(struct udma_rlimit_common *regs,
					  enum al_udma_m2s_rlimit_action act)
{
	uint32_t reg;

	switch (act) {
	case AL_UDMA_STRM_RLIMIT_ENABLE:
		reg = al_reg_read32(&regs->cfg_1s);
		reg |= UDMA_M2S_STREAM_RATE_LIMITER_CFG_1S_EN;
		al_reg_write32(&regs->cfg_1s, reg);
		break;
	case AL_UDMA_STRM_RLIMIT_PAUSE:
		reg = al_reg_read32(&regs->cfg_1s);
		reg |= UDMA_M2S_STREAM_RATE_LIMITER_CFG_1S_PAUSE;
		al_reg_write32(&regs->cfg_1s, reg);
		break;
	case AL_UDMA_STRM_RLIMIT_RESET:
		reg = al_reg_read32(&regs->sw_ctrl);
		reg |= UDMA_M2S_STREAM_RATE_LIMITER_SW_CTRL_RST_TOKEN_CNT;
		al_reg_write32(&regs->sw_ctrl, reg);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}