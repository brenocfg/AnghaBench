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
typedef  int uint8_t ;
struct TYPE_3__ {int last_f2f3; int /*<<< orphan*/  osz; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct pt_ild {int map; size_t nominal_opcode; int imm1_bytes; int imm2_bytes; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  map_map ;

/* Variables and functions */
#define  PTI_0_IMM_WIDTH_CONST_l2 142 
#define  PTI_IMM_NONE 141 
#define  PTI_IMM_hasimm_map0x0F_op0x78_l1 140 
#define  PTI_IMM_hasimm_map0x0_op0xc8_l1 139 
 int PTI_MAP_0 ; 
 int PTI_MAP_1 ; 
#define  PTI_RESOLVE_BYREG_IMM_WIDTH_map0x0_op0xc7_l1 138 
#define  PTI_RESOLVE_BYREG_IMM_WIDTH_map0x0_op0xf6_l1 137 
#define  PTI_RESOLVE_BYREG_IMM_WIDTH_map0x0_op0xf7_l1 136 
#define  PTI_SIMM8_IMM_WIDTH_CONST_l2 135 
#define  PTI_SIMMz_IMM_WIDTH_OSZ_NONTERM_DF64_EOSZ_l2 134 
#define  PTI_SIMMz_IMM_WIDTH_OSZ_NONTERM_EOSZ_l2 133 
#define  PTI_UIMM16_IMM_WIDTH_CONST_l2 132 
#define  PTI_UIMM8_IMM_WIDTH_CONST_l2 131 
#define  PTI_UIMMv_IMM_WIDTH_OSZ_NONTERM_EOSZ_l2 130 
#define  imm_bytes_map_0x0 129 
#define  imm_bytes_map_0x0F 128 
 int pte_internal ; 
 int pti_get_modrm_reg (struct pt_ild*) ; 
 int /*<<< orphan*/  pti_get_nominal_eosz (struct pt_ild*) ; 
 int /*<<< orphan*/  pti_get_nominal_eosz_df64 (struct pt_ild*) ; 
 int resolve_v (int*,int /*<<< orphan*/ ) ; 
 int resolve_z (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_imm_bytes(struct pt_ild *ild)
{
	/*: set ild->imm1_bytes and  ild->imm2_bytes for maps 0/1 */
	static uint8_t const *const map_map[] = {
		/* map 0 */ imm_bytes_map_0x0,
		/* map 1 */ imm_bytes_map_0x0F
	};
	uint8_t map, imm_code;

	if (!ild)
		return -pte_internal;

	map = ild->map;

	if ((sizeof(map_map) / sizeof(*map_map)) <= map)
		return 0;

	imm_code = map_map[map][ild->nominal_opcode];
	switch (imm_code) {
	case PTI_IMM_NONE:
	case PTI_0_IMM_WIDTH_CONST_l2:
	default:
		return 0;

	case PTI_UIMM8_IMM_WIDTH_CONST_l2:
		ild->imm1_bytes = 1;
		return 0;

	case PTI_SIMM8_IMM_WIDTH_CONST_l2:
		ild->imm1_bytes = 1;
		return 0;

	case PTI_SIMMz_IMM_WIDTH_OSZ_NONTERM_EOSZ_l2:
		/* SIMMz(eosz) */
		return resolve_z(&ild->imm1_bytes, pti_get_nominal_eosz(ild));

	case PTI_UIMMv_IMM_WIDTH_OSZ_NONTERM_EOSZ_l2:
		/* UIMMv(eosz) */
		return resolve_v(&ild->imm1_bytes, pti_get_nominal_eosz(ild));

	case PTI_UIMM16_IMM_WIDTH_CONST_l2:
		ild->imm1_bytes = 2;
		return 0;

	case PTI_SIMMz_IMM_WIDTH_OSZ_NONTERM_DF64_EOSZ_l2:
		/* push defaults to eosz64 in 64b mode, then uses SIMMz */
		return resolve_z(&ild->imm1_bytes,
				 pti_get_nominal_eosz_df64(ild));

	case PTI_RESOLVE_BYREG_IMM_WIDTH_map0x0_op0xf7_l1:
		if (ild->map == PTI_MAP_0 && pti_get_modrm_reg(ild) < 2) {
			return resolve_z(&ild->imm1_bytes,
					 pti_get_nominal_eosz(ild));
		}
		return 0;

	case PTI_RESOLVE_BYREG_IMM_WIDTH_map0x0_op0xc7_l1:
		if (ild->map == PTI_MAP_0 && pti_get_modrm_reg(ild) == 0) {
			return resolve_z(&ild->imm1_bytes,
					 pti_get_nominal_eosz(ild));
		}
		return 0;

	case PTI_RESOLVE_BYREG_IMM_WIDTH_map0x0_op0xf6_l1:
		if (ild->map == PTI_MAP_0 && pti_get_modrm_reg(ild) < 2)
			ild->imm1_bytes = 1;

		return 0;

	case PTI_IMM_hasimm_map0x0_op0xc8_l1:
		if (ild->map == PTI_MAP_0) {
			/*enter -> imm1=2, imm2=1 */
			ild->imm1_bytes = 2;
			ild->imm2_bytes = 1;
		}
		return 0;

	case PTI_IMM_hasimm_map0x0F_op0x78_l1:
		/* AMD SSE4a (insertq/extrq use  osz/f2) vs vmread
		 * (no prefixes)
		 */
		if (ild->map == PTI_MAP_1) {
			if (ild->u.s.osz || ild->u.s.last_f2f3 == 2) {
				ild->imm1_bytes = 1;
				ild->imm2_bytes = 1;
			}
		}
		return 0;
	}
}