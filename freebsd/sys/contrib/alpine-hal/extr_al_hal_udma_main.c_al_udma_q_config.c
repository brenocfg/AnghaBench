#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct al_udma_q {TYPE_4__* q_regs; TYPE_1__* udma; } ;
struct TYPE_6__ {int /*<<< orphan*/  mask; } ;
struct TYPE_7__ {TYPE_2__ rlimit; } ;
struct TYPE_8__ {TYPE_3__ m2s_q; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDMA_M2S_Q_RATE_LIMIT_MASK_INTERNAL_PAUSE_DMB ; 
 scalar_t__ UDMA_TX ; 
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int al_udma_q_config(struct al_udma_q *udma_q)
{
	uint32_t *reg_addr;
	uint32_t val;

	if (udma_q->udma->type == UDMA_TX) {
		reg_addr = &udma_q->q_regs->m2s_q.rlimit.mask;

		val = al_reg_read32(reg_addr);
		// enable DMB
		val &= ~UDMA_M2S_Q_RATE_LIMIT_MASK_INTERNAL_PAUSE_DMB;
		al_reg_write32(reg_addr, val);
	}
	return 0;
}