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
typedef  int uint8_t ;
struct pt_ild {scalar_t__ disp_bytes; int map; size_t nominal_opcode; } ;
typedef  int /*<<< orphan*/  map_map ;

/* Variables and functions */
#define  PTI_BRDISP8 136 
#define  PTI_BRDISPz_BRDISP_WIDTH_OSZ_NONTERM_EOSZ_l2 135 
#define  PTI_DISP_BUCKET_0_l1 134 
#define  PTI_DISP_NONE 133 
 int PTI_MAP_0 ; 
#define  PTI_MEMDISPv_DISP_WIDTH_ASZ_NONTERM_EASZ_l2 132 
#define  PTI_PRESERVE_DEFAULT 131 
#define  PTI_RESOLVE_BYREG_DISP_map0x0_op0xc7_l1 130 
#define  disp_bytes_map_0x0 129 
#define  disp_bytes_map_0x0F 128 
 int /*<<< orphan*/  mode_64b (struct pt_ild*) ; 
 int pte_bad_insn ; 
 int pte_internal ; 
 int pti_get_modrm_reg (struct pt_ild*) ; 
 int /*<<< orphan*/  pti_get_nominal_easz (struct pt_ild*) ; 
 int /*<<< orphan*/  pti_get_nominal_eosz (struct pt_ild*) ; 
 int resolve_v (int*,int /*<<< orphan*/ ) ; 
 int resolve_z (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compute_disp_dec(struct pt_ild *ild)
{
	/* set ild->disp_bytes for maps 0 and 1. */
	static uint8_t const *const map_map[] = {
		/* map 0 */ disp_bytes_map_0x0,
		/* map 1 */ disp_bytes_map_0x0F
	};
	uint8_t map, disp_kind;

	if (!ild)
		return -pte_internal;

	if (0 < ild->disp_bytes)
		return 0;

	map = ild->map;

	if ((sizeof(map_map) / sizeof(*map_map)) <= map)
		return 0;

	disp_kind = map_map[map][ild->nominal_opcode];
	switch (disp_kind) {
	case PTI_DISP_NONE:
		ild->disp_bytes = 0;
		return 0;

	case PTI_PRESERVE_DEFAULT:
		/* nothing to do */
		return 0;

	case PTI_BRDISP8:
		ild->disp_bytes = 1;
		return 0;

	case PTI_DISP_BUCKET_0_l1:
		/* BRDISPz(eosz) for 16/32 modes, and BRDISP32 for 64b mode */
		if (mode_64b(ild)) {
			ild->disp_bytes = 4;
			return 0;
		}

		return resolve_z(&ild->disp_bytes,
				 pti_get_nominal_eosz(ild));

	case PTI_MEMDISPv_DISP_WIDTH_ASZ_NONTERM_EASZ_l2:
		/* MEMDISPv(easz) */
		return resolve_v(&ild->disp_bytes, pti_get_nominal_easz(ild));

	case PTI_BRDISPz_BRDISP_WIDTH_OSZ_NONTERM_EOSZ_l2:
		/* BRDISPz(eosz) for 16/32/64 modes */
		return resolve_z(&ild->disp_bytes, pti_get_nominal_eosz(ild));

	case PTI_RESOLVE_BYREG_DISP_map0x0_op0xc7_l1:
		/* reg=0 -> preserve, reg=7 -> BRDISPz(eosz) */
		if (ild->map == PTI_MAP_0 && pti_get_modrm_reg(ild) == 7) {
			return resolve_z(&ild->disp_bytes,
					 pti_get_nominal_eosz(ild));
		}
		return 0;

	default:
		return -pte_bad_insn;
	}
}