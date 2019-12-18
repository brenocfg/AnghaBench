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
typedef  size_t uint32_t ;
struct al_udma {TYPE_3__* udma_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  indirect_ctrl; } ;
struct TYPE_5__ {TYPE_1__ m2s; } ;
struct TYPE_6__ {TYPE_2__ m2s; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_UDMA_PRINT_REG (struct al_udma*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_dbg (char*,size_t) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  cfg ; 
 int /*<<< orphan*/  comp_cfg ; 
 int /*<<< orphan*/  comp_cfg_2 ; 
 int /*<<< orphan*/  pkt_cfg ; 
 int /*<<< orphan*/  q_rx_pkt ; 
 int /*<<< orphan*/  qos_cfg ; 
 int /*<<< orphan*/  rcrbp_high ; 
 int /*<<< orphan*/  rcrbp_low ; 
 int /*<<< orphan*/  rcrhp ; 
 int /*<<< orphan*/  rcrhp_internal ; 
 int /*<<< orphan*/  rdcp ; 
 int /*<<< orphan*/  rdrbp_high ; 
 int /*<<< orphan*/  rdrbp_low ; 
 int /*<<< orphan*/  rdrhp ; 
 int /*<<< orphan*/  rdrl ; 
 int /*<<< orphan*/  rdrtp ; 
 int /*<<< orphan*/  s2m ; 
 int /*<<< orphan*/ * s2m_q ; 
 int /*<<< orphan*/  sel_comp_fifo_status ; 
 int /*<<< orphan*/  sel_pref_fifo_status ; 
 int /*<<< orphan*/  status ; 

__attribute__((used)) static void al_udma_regs_s2m_q_print(struct al_udma *udma, uint32_t qid)
{
	al_dbg("S2M Q[%d] status regs:\n", qid);
	al_reg_write32(&udma->udma_regs->m2s.m2s.indirect_ctrl, qid);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, sel_pref_fifo_status);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, sel_comp_fifo_status);

	al_dbg("S2M Q[%d] regs:\n", qid);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], cfg);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], status);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], rdrbp_low);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], rdrbp_high);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], rdrl);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], rdrhp);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], rdrtp);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], rdcp);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], rcrbp_low);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], rcrbp_high);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], rcrhp);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], rcrhp_internal);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], comp_cfg);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], comp_cfg_2);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], pkt_cfg);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], qos_cfg);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_q[qid], q_rx_pkt);
}