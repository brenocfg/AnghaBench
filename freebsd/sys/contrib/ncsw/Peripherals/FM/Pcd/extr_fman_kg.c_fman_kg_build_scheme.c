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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct fman_kg_scheme_regs {int kgse_mode; int kgse_ekdv; int* kgse_gec; int kgse_bmch; int kgse_bmcl; int kgse_fqb; int kgse_hc; int kgse_ppc; int /*<<< orphan*/  kgse_spc; int /*<<< orphan*/  kgse_ccbs; int /*<<< orphan*/  kgse_ekfc; int /*<<< orphan*/  kgse_dv1; int /*<<< orphan*/  kgse_dv0; int /*<<< orphan*/  kgse_mv; } ;
struct TYPE_9__ {int /*<<< orphan*/  qlcv_bits_sel; scalar_t__ base_offset; } ;
struct TYPE_8__ {scalar_t__ shift; int base; scalar_t__ mask; scalar_t__ bypass_pp_gen; } ;
struct TYPE_7__ {int mask; scalar_t__ shift_r; scalar_t__ sym; scalar_t__ use_hash; } ;
struct TYPE_10__ {int mac_addr; int vlan_tci; int etype; int ppp_sid; int ppp_pid; int mpls; int ip_addr; int ptype; int ip_tos_tc; int ipv6_fl; int ipsec_spi; int l4_port; int tcp_flg; } ;
struct fman_kg_extract_params {scalar_t__ gen_extract_num; int masks_num; TYPE_1__* masks; struct fman_kg_gen_extract_params* gen_extract; TYPE_5__ known_fields_def; int /*<<< orphan*/  known_fields; int /*<<< orphan*/  def_scheme_1; int /*<<< orphan*/  def_scheme_0; } ;
struct fman_kg_scheme_params {scalar_t__ next_engine; int base_fqid; int /*<<< orphan*/  counter_value; scalar_t__ update_counter; TYPE_4__ cc_params; TYPE_3__ policer_params; scalar_t__ bypass_fqid_gen; TYPE_2__ hash_params; struct fman_kg_extract_params extract_params; int /*<<< orphan*/  match_vector; int /*<<< orphan*/  next_engine_action; } ;
struct fman_kg_gen_extract_params {scalar_t__ type; scalar_t__ extract; int offset; int /*<<< orphan*/  no_validation; int /*<<< orphan*/  src; scalar_t__ mask; scalar_t__ def_val; } ;
struct TYPE_6__ {int field_or_gen_idx; scalar_t__ mask; scalar_t__ offset; scalar_t__ is_known; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ E_FMAN_KG_HASH_EXTRACT ; 
 scalar_t__ E_FMAN_PCD_CC ; 
 scalar_t__ E_FMAN_PCD_PLCR ; 
 int FMAN_KG_SCH_DEF_ETYPE_SHIFT ; 
 int FMAN_KG_SCH_DEF_IPSEC_SPI_SHIFT ; 
 int FMAN_KG_SCH_DEF_IP_ADDR_SHIFT ; 
 int FMAN_KG_SCH_DEF_IP_TOS_TC_SHIFT ; 
 int FMAN_KG_SCH_DEF_IPv6_FL_SHIFT ; 
 int FMAN_KG_SCH_DEF_L4_PORT_SHIFT ; 
 int FMAN_KG_SCH_DEF_MAC_ADDR_SHIFT ; 
 int FMAN_KG_SCH_DEF_MPLS_SHIFT ; 
 int FMAN_KG_SCH_DEF_PPP_PID_SHIFT ; 
 int FMAN_KG_SCH_DEF_PPP_SID_SHIFT ; 
 int FMAN_KG_SCH_DEF_PTYPE_SHIFT ; 
 int FMAN_KG_SCH_DEF_TCP_FLG_SHIFT ; 
 int FMAN_KG_SCH_DEF_VLAN_TCI_SHIFT ; 
 int FMAN_KG_SCH_GEN_DEF_SHIFT ; 
 int FMAN_KG_SCH_GEN_HT_SHIFT ; 
 int FMAN_KG_SCH_GEN_MASK_SHIFT ; 
 int FMAN_KG_SCH_GEN_OR ; 
 scalar_t__ FMAN_KG_SCH_GEN_SIZE_MAX ; 
 int FMAN_KG_SCH_GEN_SIZE_SHIFT ; 
 int FMAN_KG_SCH_GEN_VALID ; 
 scalar_t__ FMAN_KG_SCH_HASH_HSHIFT_MAX ; 
 int FMAN_KG_SCH_HASH_HSHIFT_SHIFT ; 
 int FMAN_KG_SCH_HASH_NO_FQID_GEN ; 
 int FMAN_KG_SCH_HASH_SYM ; 
 int FMAN_KG_SCH_MODE_CCOBASE_SHIFT ; 
 int FMAN_KG_SCH_MODE_EN ; 
 int FMAN_KG_SCH_MODE_NIA_PLCR ; 
 int FMAN_KG_SCH_PP_MASK_SHIFT ; 
 scalar_t__ FMAN_KG_SCH_PP_SHIFT_MAX ; 
 int FMAN_KG_SCH_PP_SH_MASK ; 
 int FMAN_KG_SCH_PP_SH_SHIFT ; 
 int FMAN_KG_SCH_PP_SL_MASK ; 
 int FMAN_KG_SCH_PP_SL_SHIFT ; 
 int FM_KG_EXTRACT_MASKS_NUM ; 
 int FM_KG_MASK_SEL_GEN_BASE ; 
 scalar_t__ FM_KG_NUM_OF_GENERIC_REGS ; 
 int /*<<< orphan*/  KG_GET_MASK_OFFSET_SHIFT (int,int) ; 
 int /*<<< orphan*/  KG_GET_MASK_SEL_SHIFT (int,int) ; 
 int /*<<< orphan*/  KG_GET_MASK_SHIFT (int,int) ; 
 int KG_NIA_INVALID ; 
 int fm_kg_build_nia (scalar_t__,int /*<<< orphan*/ ) ; 
 int get_gen_ht_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (struct fman_kg_scheme_regs*,int /*<<< orphan*/ ,int) ; 

int fman_kg_build_scheme(struct fman_kg_scheme_params *params,
				struct fman_kg_scheme_regs *scheme_regs)
{
	struct fman_kg_extract_params *extract_params;
	struct fman_kg_gen_extract_params *gen_params;
	uint32_t tmp_reg, i, select, mask, fqb;
	uint8_t offset, shift, ht;

	/* Zero out all registers so no need to care about unused ones */
	memset(scheme_regs, 0, sizeof(struct fman_kg_scheme_regs));

	/* Mode register */
	tmp_reg = fm_kg_build_nia(params->next_engine,
			params->next_engine_action);
	if (tmp_reg == KG_NIA_INVALID) {
		return -EINVAL;
	}

	if (params->next_engine == E_FMAN_PCD_PLCR) {
		tmp_reg |= FMAN_KG_SCH_MODE_NIA_PLCR;
	}
	else if (params->next_engine == E_FMAN_PCD_CC) {
		tmp_reg |= (uint32_t)params->cc_params.base_offset <<
				FMAN_KG_SCH_MODE_CCOBASE_SHIFT;
	}

	tmp_reg |= FMAN_KG_SCH_MODE_EN;
	scheme_regs->kgse_mode = tmp_reg;

	/* Match vector */
	scheme_regs->kgse_mv = params->match_vector;

	extract_params = &params->extract_params;

	/* Scheme default values registers */
	scheme_regs->kgse_dv0 = extract_params->def_scheme_0;
	scheme_regs->kgse_dv1 = extract_params->def_scheme_1;

	/* Extract Known Fields Command register */
	scheme_regs->kgse_ekfc = extract_params->known_fields;

	/* Entry Extract Known Default Value register */
	tmp_reg = 0;
	tmp_reg |= extract_params->known_fields_def.mac_addr <<
			FMAN_KG_SCH_DEF_MAC_ADDR_SHIFT;
	tmp_reg |= extract_params->known_fields_def.vlan_tci <<
			FMAN_KG_SCH_DEF_VLAN_TCI_SHIFT;
	tmp_reg |= extract_params->known_fields_def.etype <<
			FMAN_KG_SCH_DEF_ETYPE_SHIFT;
	tmp_reg |= extract_params->known_fields_def.ppp_sid <<
			FMAN_KG_SCH_DEF_PPP_SID_SHIFT;
	tmp_reg |= extract_params->known_fields_def.ppp_pid <<
			FMAN_KG_SCH_DEF_PPP_PID_SHIFT;
	tmp_reg |= extract_params->known_fields_def.mpls <<
			FMAN_KG_SCH_DEF_MPLS_SHIFT;
	tmp_reg |= extract_params->known_fields_def.ip_addr <<
			FMAN_KG_SCH_DEF_IP_ADDR_SHIFT;
	tmp_reg |= extract_params->known_fields_def.ptype <<
			FMAN_KG_SCH_DEF_PTYPE_SHIFT;
	tmp_reg |= extract_params->known_fields_def.ip_tos_tc <<
			FMAN_KG_SCH_DEF_IP_TOS_TC_SHIFT;
	tmp_reg |= extract_params->known_fields_def.ipv6_fl <<
			FMAN_KG_SCH_DEF_IPv6_FL_SHIFT;
	tmp_reg |= extract_params->known_fields_def.ipsec_spi <<
			FMAN_KG_SCH_DEF_IPSEC_SPI_SHIFT;
	tmp_reg |= extract_params->known_fields_def.l4_port <<
			FMAN_KG_SCH_DEF_L4_PORT_SHIFT;
	tmp_reg |= extract_params->known_fields_def.tcp_flg <<
			FMAN_KG_SCH_DEF_TCP_FLG_SHIFT;

	scheme_regs->kgse_ekdv = tmp_reg;

	/* Generic extract registers */
	if (extract_params->gen_extract_num > FM_KG_NUM_OF_GENERIC_REGS) {
		return -EINVAL;
	}

	for (i = 0; i < extract_params->gen_extract_num; i++) {
		gen_params = extract_params->gen_extract + i;

		tmp_reg = FMAN_KG_SCH_GEN_VALID;
		tmp_reg |= (uint32_t)gen_params->def_val <<
				FMAN_KG_SCH_GEN_DEF_SHIFT;

		if (gen_params->type == E_FMAN_KG_HASH_EXTRACT) {
			if ((gen_params->extract > FMAN_KG_SCH_GEN_SIZE_MAX) ||
					(gen_params->extract == 0)) {
				return -EINVAL;
			}
		} else {
			tmp_reg |= FMAN_KG_SCH_GEN_OR;
		}

		tmp_reg |= (uint32_t)gen_params->extract <<
				FMAN_KG_SCH_GEN_SIZE_SHIFT;
		tmp_reg |= (uint32_t)gen_params->mask <<
				FMAN_KG_SCH_GEN_MASK_SHIFT;

		offset = gen_params->offset;
		ht = get_gen_ht_code(gen_params->src,
				gen_params->no_validation,
				&offset);
		tmp_reg |= (uint32_t)ht << FMAN_KG_SCH_GEN_HT_SHIFT;
		tmp_reg |= offset;

		scheme_regs->kgse_gec[i] = tmp_reg;
	}

	/* Masks registers */
	if (extract_params->masks_num > FM_KG_EXTRACT_MASKS_NUM) {
		return -EINVAL;
	}

	select = 0;
	mask = 0;
	fqb = 0;
	for (i = 0; i < extract_params->masks_num; i++) {
		/* MCSx fields */
		KG_GET_MASK_SEL_SHIFT(shift, i);
		if (extract_params->masks[i].is_known) {
			/* Mask known field */
			select |= extract_params->masks[i].field_or_gen_idx <<
					shift;
		} else {
			/* Mask generic extract */
			select |= (extract_params->masks[i].field_or_gen_idx +
					FM_KG_MASK_SEL_GEN_BASE) << shift;
		}

		/* MOx fields - spread between se_bmch and se_fqb registers */
		KG_GET_MASK_OFFSET_SHIFT(shift, i);
		if (i < 2) {
			select |= (uint32_t)extract_params->masks[i].offset <<
					shift;
		} else {
			fqb |= (uint32_t)extract_params->masks[i].offset <<
					shift;
		}

		/* BMx fields */
		KG_GET_MASK_SHIFT(shift, i);
		mask |= (uint32_t)extract_params->masks[i].mask << shift;
	}

	/* Finish with rest of BMx fileds -
	 * don't mask bits for unused masks by setting
	 * corresponding BMx field = 0xFF */
	for (i = extract_params->masks_num; i < FM_KG_EXTRACT_MASKS_NUM; i++) {
		KG_GET_MASK_SHIFT(shift, i);
		mask |= 0xFF << shift;
	}

	scheme_regs->kgse_bmch = select;
	scheme_regs->kgse_bmcl = mask;

	/* Finish with FQB register initialization.
	 * Check fqid is 24-bit value. */
	if (params->base_fqid & ~0x00FFFFFF) {
		return -EINVAL;
	}

	fqb |= params->base_fqid;
	scheme_regs->kgse_fqb = fqb;

	/* Hash Configuration register */
	tmp_reg = 0;
	if (params->hash_params.use_hash) {
		/* Check hash mask is 24-bit value */
		if (params->hash_params.mask & ~0x00FFFFFF) {
			return -EINVAL;
		}

		/* Hash function produces 64-bit value, 24 bits of that
		 * are used to generate fq_id and policer profile.
		 * Thus, maximal shift is 40 bits to allow 24 bits out of 64.
		 */
		if (params->hash_params.shift_r > FMAN_KG_SCH_HASH_HSHIFT_MAX) {
			return -EINVAL;
		}

		tmp_reg |= params->hash_params.mask;
		tmp_reg |= (uint32_t)params->hash_params.shift_r <<
				FMAN_KG_SCH_HASH_HSHIFT_SHIFT;

		if (params->hash_params.sym) {
			tmp_reg |= FMAN_KG_SCH_HASH_SYM;
		}

	}

	if (params->bypass_fqid_gen) {
		tmp_reg |= FMAN_KG_SCH_HASH_NO_FQID_GEN;
	}

	scheme_regs->kgse_hc = tmp_reg;

	/* Policer Profile register */
	if (params->policer_params.bypass_pp_gen) {
		tmp_reg = 0;
	} else {
		/* Lower 8 bits of 24-bits extracted from hash result
		 * are used for policer profile generation.
		 * That leaves maximum shift value = 23. */
		if (params->policer_params.shift > FMAN_KG_SCH_PP_SHIFT_MAX) {
			return -EINVAL;
		}

		tmp_reg = params->policer_params.base;
		tmp_reg |= ((uint32_t)params->policer_params.shift <<
				FMAN_KG_SCH_PP_SH_SHIFT) &
				FMAN_KG_SCH_PP_SH_MASK;
		tmp_reg |= ((uint32_t)params->policer_params.shift <<
				FMAN_KG_SCH_PP_SL_SHIFT) &
				FMAN_KG_SCH_PP_SL_MASK;
		tmp_reg |= (uint32_t)params->policer_params.mask <<
				FMAN_KG_SCH_PP_MASK_SHIFT;
	}

	scheme_regs->kgse_ppc = tmp_reg;

	/* Coarse Classification Bit Select register */
	if (params->next_engine == E_FMAN_PCD_CC) {
		scheme_regs->kgse_ccbs = params->cc_params.qlcv_bits_sel;
	}

	/* Packets Counter register */
	if (params->update_counter) {
		scheme_regs->kgse_spc = params->counter_value;
	}

	return 0;
}