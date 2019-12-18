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
typedef  int uint32_t ;
struct al_udma_q {TYPE_1__* q_regs; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int /*<<< orphan*/  cfg; } ;
struct TYPE_3__ {TYPE_2__ rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_QUEUE_DISABLED ; 
 int /*<<< orphan*/  AL_QUEUE_ENABLED ; 
 int UDMA_M2S_Q_CFG_EN_PREF ; 
 int UDMA_M2S_Q_CFG_EN_SCHEDULING ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int al_udma_q_enable(struct al_udma_q *udma_q, int enable)
{
	uint32_t reg = al_reg_read32(&udma_q->q_regs->rings.cfg);

	if (enable) {
		reg |= (UDMA_M2S_Q_CFG_EN_PREF | UDMA_M2S_Q_CFG_EN_SCHEDULING);
		udma_q->status = AL_QUEUE_ENABLED;
	} else {
		reg &= ~(UDMA_M2S_Q_CFG_EN_PREF | UDMA_M2S_Q_CFG_EN_SCHEDULING);
		udma_q->status = AL_QUEUE_DISABLED;
	}
	al_reg_write32(&udma_q->q_regs->rings.cfg, reg);
	return 0;
}