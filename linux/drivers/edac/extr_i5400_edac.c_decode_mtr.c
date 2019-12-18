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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ MTR_DIMMS_ETHROTTLE (int /*<<< orphan*/ ) ; 
 int MTR_DIMMS_PRESENT (int /*<<< orphan*/ ) ; 
 int MTR_DIMM_COLS (int /*<<< orphan*/ ) ; 
 scalar_t__ MTR_DIMM_RANK (int /*<<< orphan*/ ) ; 
 int MTR_DIMM_ROWS (int /*<<< orphan*/ ) ; 
 char* MTR_DRAM_BANKS (int /*<<< orphan*/ ) ; 
 char* MTR_DRAM_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,...) ; 

__attribute__((used)) static void decode_mtr(int slot_row, u16 mtr)
{
	int ans;

	ans = MTR_DIMMS_PRESENT(mtr);

	edac_dbg(2, "\tMTR%d=0x%x:  DIMMs are %sPresent\n",
		 slot_row, mtr, ans ? "" : "NOT ");
	if (!ans)
		return;

	edac_dbg(2, "\t\tWIDTH: x%d\n", MTR_DRAM_WIDTH(mtr));

	edac_dbg(2, "\t\tELECTRICAL THROTTLING is %s\n",
		 MTR_DIMMS_ETHROTTLE(mtr) ? "enabled" : "disabled");

	edac_dbg(2, "\t\tNUMBANK: %d bank(s)\n", MTR_DRAM_BANKS(mtr));
	edac_dbg(2, "\t\tNUMRANK: %s\n",
		 MTR_DIMM_RANK(mtr) ? "double" : "single");
	edac_dbg(2, "\t\tNUMROW: %s\n",
		 MTR_DIMM_ROWS(mtr) == 0 ? "8,192 - 13 rows" :
		 MTR_DIMM_ROWS(mtr) == 1 ? "16,384 - 14 rows" :
		 MTR_DIMM_ROWS(mtr) == 2 ? "32,768 - 15 rows" :
		 "65,536 - 16 rows");
	edac_dbg(2, "\t\tNUMCOL: %s\n",
		 MTR_DIMM_COLS(mtr) == 0 ? "1,024 - 10 columns" :
		 MTR_DIMM_COLS(mtr) == 1 ? "2,048 - 11 columns" :
		 MTR_DIMM_COLS(mtr) == 2 ? "4,096 - 12 columns" :
		 "reserved");
}