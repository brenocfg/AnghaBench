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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_4__ {int (* get_tolm ) (struct sbridge_pvt*) ;int (* get_tohm ) (struct sbridge_pvt*) ;int max_sad; int (* sad_limit ) (int) ;scalar_t__ type; int (* rir_limit ) (int) ;int /*<<< orphan*/  interleave_pkg; int /*<<< orphan*/ * interleave_list; int /*<<< orphan*/  (* dram_attr ) (int) ;int /*<<< orphan*/ * dram_rule; } ;
struct sbridge_pvt {int tolm; int tohm; TYPE_2__ info; int /*<<< orphan*/ * pci_tad; TYPE_1__* channel; int /*<<< orphan*/  pci_ha; int /*<<< orphan*/  pci_sad0; } ;
struct mem_ctl_info {struct sbridge_pvt* pvt_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  dimms; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRAM_RULE_ENABLE (int) ; 
 int /*<<< orphan*/  IS_RIR_VALID (int) ; 
 scalar_t__ KNIGHTS_LANDING ; 
 int MAX_RIR_RANGES ; 
 int MAX_TAD ; 
 int NUM_CHANNELS ; 
 int RIR_OFFSET (scalar_t__,int) ; 
 scalar_t__ RIR_RNK_TGT (scalar_t__,int) ; 
 int RIR_WAY (int) ; 
 scalar_t__ TAD_CH (int) ; 
 int TAD_LIMIT (int) ; 
 int TAD_OFFSET (int) ; 
 int TAD_SOCK (int) ; 
 scalar_t__ TAD_TGT0 (int) ; 
 scalar_t__ TAD_TGT1 (int) ; 
 scalar_t__ TAD_TGT2 (int) ; 
 scalar_t__ TAD_TGT3 (int) ; 
 int div_u64_rem (int,int,int*) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int /*<<< orphan*/  get_intlv_mode_str (int,scalar_t__) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ ** rir_offset ; 
 int /*<<< orphan*/ * rir_way_limit ; 
 int sad_pkg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  show_dram_attr (int /*<<< orphan*/ ) ; 
 int stub1 (struct sbridge_pvt*) ; 
 int stub2 (struct sbridge_pvt*) ; 
 int stub3 (int) ; 
 int /*<<< orphan*/  stub4 (int) ; 
 int stub5 (int) ; 
 int /*<<< orphan*/ * tad_ch_nilv_offset ; 
 int /*<<< orphan*/ * tad_dram_rule ; 

__attribute__((used)) static void get_memory_layout(const struct mem_ctl_info *mci)
{
	struct sbridge_pvt *pvt = mci->pvt_info;
	int i, j, k, n_sads, n_tads, sad_interl;
	u32 reg;
	u64 limit, prv = 0;
	u64 tmp_mb;
	u32 gb, mb;
	u32 rir_way;

	/*
	 * Step 1) Get TOLM/TOHM ranges
	 */

	pvt->tolm = pvt->info.get_tolm(pvt);
	tmp_mb = (1 + pvt->tolm) >> 20;

	gb = div_u64_rem(tmp_mb, 1024, &mb);
	edac_dbg(0, "TOLM: %u.%03u GB (0x%016Lx)\n",
		gb, (mb*1000)/1024, (u64)pvt->tolm);

	/* Address range is already 45:25 */
	pvt->tohm = pvt->info.get_tohm(pvt);
	tmp_mb = (1 + pvt->tohm) >> 20;

	gb = div_u64_rem(tmp_mb, 1024, &mb);
	edac_dbg(0, "TOHM: %u.%03u GB (0x%016Lx)\n",
		gb, (mb*1000)/1024, (u64)pvt->tohm);

	/*
	 * Step 2) Get SAD range and SAD Interleave list
	 * TAD registers contain the interleave wayness. However, it
	 * seems simpler to just discover it indirectly, with the
	 * algorithm bellow.
	 */
	prv = 0;
	for (n_sads = 0; n_sads < pvt->info.max_sad; n_sads++) {
		/* SAD_LIMIT Address range is 45:26 */
		pci_read_config_dword(pvt->pci_sad0, pvt->info.dram_rule[n_sads],
				      &reg);
		limit = pvt->info.sad_limit(reg);

		if (!DRAM_RULE_ENABLE(reg))
			continue;

		if (limit <= prv)
			break;

		tmp_mb = (limit + 1) >> 20;
		gb = div_u64_rem(tmp_mb, 1024, &mb);
		edac_dbg(0, "SAD#%d %s up to %u.%03u GB (0x%016Lx) Interleave: %s reg=0x%08x\n",
			 n_sads,
			 show_dram_attr(pvt->info.dram_attr(reg)),
			 gb, (mb*1000)/1024,
			 ((u64)tmp_mb) << 20L,
			 get_intlv_mode_str(reg, pvt->info.type),
			 reg);
		prv = limit;

		pci_read_config_dword(pvt->pci_sad0, pvt->info.interleave_list[n_sads],
				      &reg);
		sad_interl = sad_pkg(pvt->info.interleave_pkg, reg, 0);
		for (j = 0; j < 8; j++) {
			u32 pkg = sad_pkg(pvt->info.interleave_pkg, reg, j);
			if (j > 0 && sad_interl == pkg)
				break;

			edac_dbg(0, "SAD#%d, interleave #%d: %d\n",
				 n_sads, j, pkg);
		}
	}

	if (pvt->info.type == KNIGHTS_LANDING)
		return;

	/*
	 * Step 3) Get TAD range
	 */
	prv = 0;
	for (n_tads = 0; n_tads < MAX_TAD; n_tads++) {
		pci_read_config_dword(pvt->pci_ha, tad_dram_rule[n_tads], &reg);
		limit = TAD_LIMIT(reg);
		if (limit <= prv)
			break;
		tmp_mb = (limit + 1) >> 20;

		gb = div_u64_rem(tmp_mb, 1024, &mb);
		edac_dbg(0, "TAD#%d: up to %u.%03u GB (0x%016Lx), socket interleave %d, memory interleave %d, TGT: %d, %d, %d, %d, reg=0x%08x\n",
			 n_tads, gb, (mb*1000)/1024,
			 ((u64)tmp_mb) << 20L,
			 (u32)(1 << TAD_SOCK(reg)),
			 (u32)TAD_CH(reg) + 1,
			 (u32)TAD_TGT0(reg),
			 (u32)TAD_TGT1(reg),
			 (u32)TAD_TGT2(reg),
			 (u32)TAD_TGT3(reg),
			 reg);
		prv = limit;
	}

	/*
	 * Step 4) Get TAD offsets, per each channel
	 */
	for (i = 0; i < NUM_CHANNELS; i++) {
		if (!pvt->channel[i].dimms)
			continue;
		for (j = 0; j < n_tads; j++) {
			pci_read_config_dword(pvt->pci_tad[i],
					      tad_ch_nilv_offset[j],
					      &reg);
			tmp_mb = TAD_OFFSET(reg) >> 20;
			gb = div_u64_rem(tmp_mb, 1024, &mb);
			edac_dbg(0, "TAD CH#%d, offset #%d: %u.%03u GB (0x%016Lx), reg=0x%08x\n",
				 i, j,
				 gb, (mb*1000)/1024,
				 ((u64)tmp_mb) << 20L,
				 reg);
		}
	}

	/*
	 * Step 6) Get RIR Wayness/Limit, per each channel
	 */
	for (i = 0; i < NUM_CHANNELS; i++) {
		if (!pvt->channel[i].dimms)
			continue;
		for (j = 0; j < MAX_RIR_RANGES; j++) {
			pci_read_config_dword(pvt->pci_tad[i],
					      rir_way_limit[j],
					      &reg);

			if (!IS_RIR_VALID(reg))
				continue;

			tmp_mb = pvt->info.rir_limit(reg) >> 20;
			rir_way = 1 << RIR_WAY(reg);
			gb = div_u64_rem(tmp_mb, 1024, &mb);
			edac_dbg(0, "CH#%d RIR#%d, limit: %u.%03u GB (0x%016Lx), way: %d, reg=0x%08x\n",
				 i, j,
				 gb, (mb*1000)/1024,
				 ((u64)tmp_mb) << 20L,
				 rir_way,
				 reg);

			for (k = 0; k < rir_way; k++) {
				pci_read_config_dword(pvt->pci_tad[i],
						      rir_offset[j][k],
						      &reg);
				tmp_mb = RIR_OFFSET(pvt->info.type, reg) << 6;

				gb = div_u64_rem(tmp_mb, 1024, &mb);
				edac_dbg(0, "CH#%d RIR#%d INTL#%d, offset %u.%03u GB (0x%016Lx), tgt: %d, reg=0x%08x\n",
					 i, j, k,
					 gb, (mb*1000)/1024,
					 ((u64)tmp_mb) << 20L,
					 (u32)RIR_RNK_TGT(pvt->info.type, reg),
					 reg);
			}
		}
	}
}