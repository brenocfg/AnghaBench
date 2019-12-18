#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct al_udma_q {TYPE_2__* q_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  dwrr_sw_ctrl; } ;
struct TYPE_4__ {TYPE_1__ m2s_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDMA_M2S_Q_DWRR_SW_CTRL_RST_CNT ; 
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int al_udma_m2s_q_sc_reset(struct al_udma_q *udma_q)
{
	uint32_t reg = al_reg_read32(&udma_q->q_regs->m2s_q.dwrr_sw_ctrl);

	reg |= UDMA_M2S_Q_DWRR_SW_CTRL_RST_CNT;
	al_reg_write32(&udma_q->q_regs->m2s_q.dwrr_sw_ctrl, reg);

	return 0;
}