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
typedef  scalar_t__ uint32_t ;
struct al_udma {TYPE_3__* udma_regs; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ al_bool ;
struct TYPE_4__ {int /*<<< orphan*/  data_cfg_2; } ;
struct TYPE_5__ {TYPE_1__ s2m_wr; } ;
struct TYPE_6__ {TYPE_2__ s2m; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_REG_FIELD_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ AL_TRUE ; 
 int EINVAL ; 
 int /*<<< orphan*/  UDMA_S2M_WR_DATA_CFG_2_DESC_WAIT_TIMER_MASK ; 
 int /*<<< orphan*/  UDMA_S2M_WR_DATA_CFG_2_DESC_WAIT_TIMER_SHIFT ; 
 scalar_t__ UDMA_S2M_WR_DATA_CFG_2_DROP_IF_NO_DESC ; 
 scalar_t__ UDMA_S2M_WR_DATA_CFG_2_HINT_IF_NO_DESC ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,scalar_t__) ; 

int al_udma_s2m_no_desc_cfg_set(struct al_udma *udma, al_bool drop_packet, al_bool gen_interrupt, uint32_t wait_for_desc_timeout)
{
	uint32_t reg;

	reg = al_reg_read32(&udma->udma_regs->s2m.s2m_wr.data_cfg_2);

	if ((drop_packet == AL_TRUE) && (wait_for_desc_timeout == 0)) {
		al_err("udam [%s]: setting timeout to 0 will cause the udma to wait forever instead of dropping the packet", udma->name);
		return -EINVAL;
	}

	if (drop_packet == AL_TRUE)
		reg |= UDMA_S2M_WR_DATA_CFG_2_DROP_IF_NO_DESC;
	else
		reg &= ~UDMA_S2M_WR_DATA_CFG_2_DROP_IF_NO_DESC;

	if (gen_interrupt == AL_TRUE)
		reg |= UDMA_S2M_WR_DATA_CFG_2_HINT_IF_NO_DESC;
	else
		reg &= ~UDMA_S2M_WR_DATA_CFG_2_HINT_IF_NO_DESC;

	AL_REG_FIELD_SET(reg, UDMA_S2M_WR_DATA_CFG_2_DESC_WAIT_TIMER_MASK, UDMA_S2M_WR_DATA_CFG_2_DESC_WAIT_TIMER_SHIFT, wait_for_desc_timeout);

	al_reg_write32(&udma->udma_regs->s2m.s2m_wr.data_cfg_2, reg);

	return 0;
}