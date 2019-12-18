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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int max_sad; int (* sad_limit ) (scalar_t__) ;int /*<<< orphan*/  interleave_pkg; int /*<<< orphan*/ * interleave_list; int /*<<< orphan*/ * dram_rule; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pci_cha; } ;
struct sbridge_pvt {TYPE_2__ info; int /*<<< orphan*/  pci_sad0; TYPE_1__ knl; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRAM_RULE_ENABLE (scalar_t__) ; 
 int /*<<< orphan*/  KNL_EDC_ROUTE ; 
 int KNL_EDRAM_ONLY (scalar_t__) ; 
 int KNL_MAX_CHANNELS ; 
 int KNL_MAX_CHAS ; 
 int KNL_MAX_EDCS ; 
 int /*<<< orphan*/  KNL_MC_ROUTE ; 
 scalar_t__ KNL_MOD3 (scalar_t__) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,...) ; 
 int knl_channel_mc (int) ; 
 int knl_get_mc_route (int,scalar_t__) ; 
 scalar_t__ knl_get_tad (struct sbridge_pvt*,int,int,int*,int*,int*) ; 
 int /*<<< orphan*/  knl_show_edc_route (scalar_t__,char*) ; 
 int /*<<< orphan*/  knl_show_mc_route (scalar_t__,char*) ; 
 int /*<<< orphan*/  knl_tad_dram_limit_lo ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ sad_pkg (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int stub1 (scalar_t__) ; 

__attribute__((used)) static int knl_get_dimm_capacity(struct sbridge_pvt *pvt, u64 *mc_sizes)
{
	u64 sad_base, sad_size, sad_limit = 0;
	u64 tad_base, tad_size, tad_limit, tad_deadspace, tad_livespace;
	int sad_rule = 0;
	int tad_rule = 0;
	int intrlv_ways, tad_ways;
	u32 first_pkg, pkg;
	int i;
	u64 sad_actual_size[2]; /* sad size accounting for holes, per mc */
	u32 dram_rule, interleave_reg;
	u32 mc_route_reg[KNL_MAX_CHAS];
	u32 edc_route_reg[KNL_MAX_CHAS];
	int edram_only;
	char edc_route_string[KNL_MAX_EDCS*2];
	char mc_route_string[KNL_MAX_CHANNELS*2];
	int cur_reg_start;
	int mc;
	int channel;
	int participants[KNL_MAX_CHANNELS];

	for (i = 0; i < KNL_MAX_CHANNELS; i++)
		mc_sizes[i] = 0;

	/* Read the EDC route table in each CHA. */
	cur_reg_start = 0;
	for (i = 0; i < KNL_MAX_CHAS; i++) {
		pci_read_config_dword(pvt->knl.pci_cha[i],
				KNL_EDC_ROUTE, &edc_route_reg[i]);

		if (i > 0 && edc_route_reg[i] != edc_route_reg[i-1]) {
			knl_show_edc_route(edc_route_reg[i-1],
					edc_route_string);
			if (cur_reg_start == i-1)
				edac_dbg(0, "edc route table for CHA %d: %s\n",
					cur_reg_start, edc_route_string);
			else
				edac_dbg(0, "edc route table for CHA %d-%d: %s\n",
					cur_reg_start, i-1, edc_route_string);
			cur_reg_start = i;
		}
	}
	knl_show_edc_route(edc_route_reg[i-1], edc_route_string);
	if (cur_reg_start == i-1)
		edac_dbg(0, "edc route table for CHA %d: %s\n",
			cur_reg_start, edc_route_string);
	else
		edac_dbg(0, "edc route table for CHA %d-%d: %s\n",
			cur_reg_start, i-1, edc_route_string);

	/* Read the MC route table in each CHA. */
	cur_reg_start = 0;
	for (i = 0; i < KNL_MAX_CHAS; i++) {
		pci_read_config_dword(pvt->knl.pci_cha[i],
			KNL_MC_ROUTE, &mc_route_reg[i]);

		if (i > 0 && mc_route_reg[i] != mc_route_reg[i-1]) {
			knl_show_mc_route(mc_route_reg[i-1], mc_route_string);
			if (cur_reg_start == i-1)
				edac_dbg(0, "mc route table for CHA %d: %s\n",
					cur_reg_start, mc_route_string);
			else
				edac_dbg(0, "mc route table for CHA %d-%d: %s\n",
					cur_reg_start, i-1, mc_route_string);
			cur_reg_start = i;
		}
	}
	knl_show_mc_route(mc_route_reg[i-1], mc_route_string);
	if (cur_reg_start == i-1)
		edac_dbg(0, "mc route table for CHA %d: %s\n",
			cur_reg_start, mc_route_string);
	else
		edac_dbg(0, "mc route table for CHA %d-%d: %s\n",
			cur_reg_start, i-1, mc_route_string);

	/* Process DRAM rules */
	for (sad_rule = 0; sad_rule < pvt->info.max_sad; sad_rule++) {
		/* previous limit becomes the new base */
		sad_base = sad_limit;

		pci_read_config_dword(pvt->pci_sad0,
			pvt->info.dram_rule[sad_rule], &dram_rule);

		if (!DRAM_RULE_ENABLE(dram_rule))
			break;

		edram_only = KNL_EDRAM_ONLY(dram_rule);

		sad_limit = pvt->info.sad_limit(dram_rule)+1;
		sad_size = sad_limit - sad_base;

		pci_read_config_dword(pvt->pci_sad0,
			pvt->info.interleave_list[sad_rule], &interleave_reg);

		/*
		 * Find out how many ways this dram rule is interleaved.
		 * We stop when we see the first channel again.
		 */
		first_pkg = sad_pkg(pvt->info.interleave_pkg,
						interleave_reg, 0);
		for (intrlv_ways = 1; intrlv_ways < 8; intrlv_ways++) {
			pkg = sad_pkg(pvt->info.interleave_pkg,
						interleave_reg, intrlv_ways);

			if ((pkg & 0x8) == 0) {
				/*
				 * 0 bit means memory is non-local,
				 * which KNL doesn't support
				 */
				edac_dbg(0, "Unexpected interleave target %d\n",
					pkg);
				return -1;
			}

			if (pkg == first_pkg)
				break;
		}
		if (KNL_MOD3(dram_rule))
			intrlv_ways *= 3;

		edac_dbg(3, "dram rule %d (base 0x%llx, limit 0x%llx), %d way interleave%s\n",
			sad_rule,
			sad_base,
			sad_limit,
			intrlv_ways,
			edram_only ? ", EDRAM" : "");

		/*
		 * Find out how big the SAD region really is by iterating
		 * over TAD tables (SAD regions may contain holes).
		 * Each memory controller might have a different TAD table, so
		 * we have to look at both.
		 *
		 * Livespace is the memory that's mapped in this TAD table,
		 * deadspace is the holes (this could be the MMIO hole, or it
		 * could be memory that's mapped by the other TAD table but
		 * not this one).
		 */
		for (mc = 0; mc < 2; mc++) {
			sad_actual_size[mc] = 0;
			tad_livespace = 0;
			for (tad_rule = 0;
					tad_rule < ARRAY_SIZE(
						knl_tad_dram_limit_lo);
					tad_rule++) {
				if (knl_get_tad(pvt,
						tad_rule,
						mc,
						&tad_deadspace,
						&tad_limit,
						&tad_ways))
					break;

				tad_size = (tad_limit+1) -
					(tad_livespace + tad_deadspace);
				tad_livespace += tad_size;
				tad_base = (tad_limit+1) - tad_size;

				if (tad_base < sad_base) {
					if (tad_limit > sad_base)
						edac_dbg(0, "TAD region overlaps lower SAD boundary -- TAD tables may be configured incorrectly.\n");
				} else if (tad_base < sad_limit) {
					if (tad_limit+1 > sad_limit) {
						edac_dbg(0, "TAD region overlaps upper SAD boundary -- TAD tables may be configured incorrectly.\n");
					} else {
						/* TAD region is completely inside SAD region */
						edac_dbg(3, "TAD region %d 0x%llx - 0x%llx (%lld bytes) table%d\n",
							tad_rule, tad_base,
							tad_limit, tad_size,
							mc);
						sad_actual_size[mc] += tad_size;
					}
				}
			}
		}

		for (mc = 0; mc < 2; mc++) {
			edac_dbg(3, " total TAD DRAM footprint in table%d : 0x%llx (%lld bytes)\n",
				mc, sad_actual_size[mc], sad_actual_size[mc]);
		}

		/* Ignore EDRAM rule */
		if (edram_only)
			continue;

		/* Figure out which channels participate in interleave. */
		for (channel = 0; channel < KNL_MAX_CHANNELS; channel++)
			participants[channel] = 0;

		/* For each channel, does at least one CHA have
		 * this channel mapped to the given target?
		 */
		for (channel = 0; channel < KNL_MAX_CHANNELS; channel++) {
			int target;
			int cha;

			for (target = 0; target < KNL_MAX_CHANNELS; target++) {
				for (cha = 0; cha < KNL_MAX_CHAS; cha++) {
					if (knl_get_mc_route(target,
						mc_route_reg[cha]) == channel
						&& !participants[channel]) {
						participants[channel] = 1;
						break;
					}
				}
			}
		}

		for (channel = 0; channel < KNL_MAX_CHANNELS; channel++) {
			mc = knl_channel_mc(channel);
			if (participants[channel]) {
				edac_dbg(4, "mc channel %d contributes %lld bytes via sad entry %d\n",
					channel,
					sad_actual_size[mc]/intrlv_ways,
					sad_rule);
				mc_sizes[channel] +=
					sad_actual_size[mc]/intrlv_ways;
			}
		}
	}

	return 0;
}