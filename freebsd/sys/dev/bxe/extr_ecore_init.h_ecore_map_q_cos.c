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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ECORE_E3B0_PORT1_COS_OFFSET ; 
 int ECORE_PF_Q_NUM (int,scalar_t__,int) ; 
 int ECORE_PORT2_MODE_NUM_VNICS ; 
 int ECORE_PORT4_MODE_NUM_VNICS ; 
 int ECORE_Q_CMDQ_REG_ADDR (int) ; 
 int ECORE_Q_VOQ_REG_ADDR (int) ; 
 int ECORE_VOQ_Q_REG_ADDR (int,int) ; 
 int INIT_MODE_FLAGS (struct bxe_softc*) ; 
 int MODE_E3_B0 ; 
 int MODE_PORT4 ; 
 scalar_t__ PORT_ID (struct bxe_softc*) ; 
 int QM_REG_QVOQIDX_0 ; 
 int REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 

__attribute__((used)) static inline void ecore_map_q_cos(struct bxe_softc *sc, uint32_t q_num, uint32_t new_cos)
{
	/* find current COS mapping */
	uint32_t curr_cos = REG_RD(sc, QM_REG_QVOQIDX_0 + q_num * 4);

	/* check if queue->COS mapping has changed */
	if (curr_cos != new_cos) {
		uint32_t num_vnics = ECORE_PORT2_MODE_NUM_VNICS;
		uint32_t reg_addr, reg_bit_map, vnic;

		/* update parameters for 4port mode */
		if (INIT_MODE_FLAGS(sc) & MODE_PORT4) {
			num_vnics = ECORE_PORT4_MODE_NUM_VNICS;
			if (PORT_ID(sc)) {
				curr_cos += ECORE_E3B0_PORT1_COS_OFFSET;
				new_cos += ECORE_E3B0_PORT1_COS_OFFSET;
			}
		}

		/* change queue mapping for each VNIC */
		for (vnic = 0; vnic < num_vnics; vnic++) {
			uint32_t pf_q_num =
				ECORE_PF_Q_NUM(q_num, PORT_ID(sc), vnic);
			uint32_t q_bit_map = 1 << (pf_q_num & 0x1f);

			/* overwrite queue->VOQ mapping */
			REG_WR(sc, ECORE_Q_VOQ_REG_ADDR(pf_q_num), new_cos);

			/* clear queue bit from current COS bit map */
			reg_addr = ECORE_VOQ_Q_REG_ADDR(curr_cos, pf_q_num);
			reg_bit_map = REG_RD(sc, reg_addr);
			REG_WR(sc, reg_addr, reg_bit_map & (~q_bit_map));

			/* set queue bit in new COS bit map */
			reg_addr = ECORE_VOQ_Q_REG_ADDR(new_cos, pf_q_num);
			reg_bit_map = REG_RD(sc, reg_addr);
			REG_WR(sc, reg_addr, reg_bit_map | q_bit_map);

			/* set/clear queue bit in command-queue bit map
			(E2/E3A0 only, valid COS values are 0/1) */
			if (!(INIT_MODE_FLAGS(sc) & MODE_E3_B0)) {
				reg_addr = ECORE_Q_CMDQ_REG_ADDR(pf_q_num);
				reg_bit_map = REG_RD(sc, reg_addr);
				q_bit_map = 1 << (2 * (pf_q_num & 0xf));
				reg_bit_map = new_cos ?
					      (reg_bit_map | q_bit_map) :
					      (reg_bit_map & (~q_bit_map));
				REG_WR(sc, reg_addr, reg_bit_map);
			}
		}
	}
}