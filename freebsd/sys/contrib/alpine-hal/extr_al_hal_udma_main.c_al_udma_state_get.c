#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct al_udma {scalar_t__ type; TYPE_5__* udma_regs; } ;
typedef  enum al_udma_state { ____Placeholder_al_udma_state } al_udma_state ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
struct TYPE_9__ {TYPE_3__ s2m; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_7__ {TYPE_1__ m2s; } ;
struct TYPE_10__ {TYPE_4__ s2m; TYPE_2__ m2s; } ;

/* Variables and functions */
 scalar_t__ AL_REG_FIELD_GET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UDMA_ABORT ; 
 int UDMA_IDLE ; 
 int /*<<< orphan*/  UDMA_M2S_STATE_COMP_CTRL_MASK ; 
 int /*<<< orphan*/  UDMA_M2S_STATE_COMP_CTRL_SHIFT ; 
 int /*<<< orphan*/  UDMA_M2S_STATE_DATA_RD_CTRL_MASK ; 
 int /*<<< orphan*/  UDMA_M2S_STATE_DATA_RD_CTRL_SHIFT ; 
 int /*<<< orphan*/  UDMA_M2S_STATE_DESC_PREF_MASK ; 
 int /*<<< orphan*/  UDMA_M2S_STATE_DESC_PREF_SHIFT ; 
 int /*<<< orphan*/  UDMA_M2S_STATE_STREAM_IF_MASK ; 
 int /*<<< orphan*/  UDMA_M2S_STATE_STREAM_IF_SHIFT ; 
 int UDMA_NORMAL ; 
 scalar_t__ UDMA_STATE_ABORT ; 
 scalar_t__ UDMA_STATE_NORMAL ; 
 scalar_t__ UDMA_STATE_RESERVED ; 
 scalar_t__ UDMA_TX ; 
 int /*<<< orphan*/  al_assert (int) ; 
 scalar_t__ al_reg_read32 (int /*<<< orphan*/ *) ; 

enum al_udma_state al_udma_state_get(struct al_udma *udma)
{
	uint32_t state_reg;
	uint32_t comp_ctrl;
	uint32_t stream_if;
	uint32_t data_rd;
	uint32_t desc_pref;

	if (udma->type == UDMA_TX)
		state_reg = al_reg_read32(&udma->udma_regs->m2s.m2s.state);
	else
		state_reg = al_reg_read32(&udma->udma_regs->s2m.s2m.state);

	comp_ctrl = AL_REG_FIELD_GET(state_reg,
				     UDMA_M2S_STATE_COMP_CTRL_MASK,
				     UDMA_M2S_STATE_COMP_CTRL_SHIFT);
	stream_if = AL_REG_FIELD_GET(state_reg,
				     UDMA_M2S_STATE_STREAM_IF_MASK,
				     UDMA_M2S_STATE_STREAM_IF_SHIFT);
	data_rd = AL_REG_FIELD_GET(state_reg,
				   UDMA_M2S_STATE_DATA_RD_CTRL_MASK,
				   UDMA_M2S_STATE_DATA_RD_CTRL_SHIFT);
	desc_pref = AL_REG_FIELD_GET(state_reg,
				     UDMA_M2S_STATE_DESC_PREF_MASK,
				     UDMA_M2S_STATE_DESC_PREF_SHIFT);

	al_assert(comp_ctrl != UDMA_STATE_RESERVED);
	al_assert(stream_if != UDMA_STATE_RESERVED);
	al_assert(data_rd != UDMA_STATE_RESERVED);
	al_assert(desc_pref != UDMA_STATE_RESERVED);

	/* if any of the states is abort then return abort */
	if ((comp_ctrl == UDMA_STATE_ABORT) || (stream_if == UDMA_STATE_ABORT)
			|| (data_rd == UDMA_STATE_ABORT)
			|| (desc_pref == UDMA_STATE_ABORT))
		return UDMA_ABORT;

	/* if any of the states is normal then return normal */
	if ((comp_ctrl == UDMA_STATE_NORMAL)
			|| (stream_if == UDMA_STATE_NORMAL)
			|| (data_rd == UDMA_STATE_NORMAL)
			|| (desc_pref == UDMA_STATE_NORMAL))
		return UDMA_NORMAL;

	return UDMA_IDLE;
}