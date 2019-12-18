#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_12__ {int /*<<< orphan*/  cfg_application_ack; } ;
struct TYPE_9__ {int /*<<< orphan*/  data_cfg; } ;
struct TYPE_13__ {TYPE_4__ m2s_comp; TYPE_1__ m2s_rd; } ;
struct TYPE_10__ {int /*<<< orphan*/  cfg_1; } ;
struct TYPE_11__ {TYPE_2__ axi; } ;
struct unit_regs {TYPE_5__ m2s; TYPE_3__ gen; } ;
struct al_udma {scalar_t__ rev_id; scalar_t__ type; TYPE_8__* udma_regs; } ;
struct TYPE_14__ {int /*<<< orphan*/  cfg_application_ack; } ;
struct TYPE_15__ {TYPE_6__ s2m_comp; } ;
struct TYPE_16__ {TYPE_7__ s2m; } ;

/* Variables and functions */
 scalar_t__ AL_UDMA_REV_ID_2 ; 
 int /*<<< orphan*/  UDMA_M2S_RD_DATA_CFG_DATA_FIFO_DEPTH_MASK ; 
 int UDMA_M2S_RD_DATA_CFG_DATA_FIFO_DEPTH_SHIFT ; 
 scalar_t__ UDMA_RX ; 
 scalar_t__ UDMA_TX ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void al_udma_set_defaults(struct al_udma *udma)
{
	uint8_t rev_id = udma->rev_id;

	if (udma->type == UDMA_TX) {
		struct unit_regs* tmp_unit_regs =
			(struct unit_regs*)udma->udma_regs;

		/* Setting the data fifo depth to 4K (256 strips of 16B)
		 * This allows the UDMA to have 16 outstanding writes */
		if (rev_id >= AL_UDMA_REV_ID_2) {
			al_reg_write32_masked(&tmp_unit_regs->m2s.m2s_rd.data_cfg,
			      UDMA_M2S_RD_DATA_CFG_DATA_FIFO_DEPTH_MASK,
			      256 << UDMA_M2S_RD_DATA_CFG_DATA_FIFO_DEPTH_SHIFT);
		}

		/* set AXI timeout to 1M (~2.6 ms) */
		al_reg_write32(&tmp_unit_regs->gen.axi.cfg_1, 1000000);

		al_reg_write32(&tmp_unit_regs->m2s.m2s_comp.cfg_application_ack
					, 0); /* Ack time out */
	}
	if (udma->type == UDMA_RX) {
		al_reg_write32(
			&udma->udma_regs->s2m.s2m_comp.cfg_application_ack, 0);
					/* Ack time out */

	}
}