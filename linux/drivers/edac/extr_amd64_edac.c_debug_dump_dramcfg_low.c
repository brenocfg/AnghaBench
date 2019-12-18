#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct amd64_pvt {scalar_t__ dram_type; int fam; TYPE_1__* csels; } ;
struct TYPE_2__ {int* csmasks; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ MEM_LRDDR3 ; 
 int /*<<< orphan*/  edac_dbg (int,char*,...) ; 

__attribute__((used)) static void debug_dump_dramcfg_low(struct amd64_pvt *pvt, u32 dclr, int chan)
{
	edac_dbg(1, "F2x%d90 (DRAM Cfg Low): 0x%08x\n", chan, dclr);

	if (pvt->dram_type == MEM_LRDDR3) {
		u32 dcsm = pvt->csels[chan].csmasks[0];
		/*
		 * It's assumed all LRDIMMs in a DCT are going to be of
		 * same 'type' until proven otherwise. So, use a cs
		 * value of '0' here to get dcsm value.
		 */
		edac_dbg(1, " LRDIMM %dx rank multiply\n", (dcsm & 0x3));
	}

	edac_dbg(1, "All DIMMs support ECC:%s\n",
		    (dclr & BIT(19)) ? "yes" : "no");


	edac_dbg(1, "  PAR/ERR parity: %s\n",
		 (dclr & BIT(8)) ?  "enabled" : "disabled");

	if (pvt->fam == 0x10)
		edac_dbg(1, "  DCT 128bit mode width: %s\n",
			 (dclr & BIT(11)) ?  "128b" : "64b");

	edac_dbg(1, "  x4 logical DIMMs present: L0: %s L1: %s L2: %s L3: %s\n",
		 (dclr & BIT(12)) ?  "yes" : "no",
		 (dclr & BIT(13)) ?  "yes" : "no",
		 (dclr & BIT(14)) ?  "yes" : "no",
		 (dclr & BIT(15)) ?  "yes" : "no");
}