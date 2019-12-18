#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mem_ctl_info {TYPE_3__** csrows; } ;
struct i82975x_error_info {int errsts2; int errsts; int eap; int xeap; int /*<<< orphan*/  derrsyn; } ;
struct TYPE_6__ {int nr_channels; TYPE_2__** channels; } ;
struct TYPE_5__ {TYPE_1__* dimm; } ;
struct TYPE_4__ {int grain; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 int /*<<< orphan*/  HW_EVENT_ERR_UNCORRECTED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int PAGE_SHIFT ; 
 int edac_mc_find_csrow_by_page (struct mem_ctl_info*,unsigned long) ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,unsigned long,unsigned long,int /*<<< orphan*/ ,int,int,int,char*,char*) ; 
 int /*<<< orphan*/  i82975x_mc_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*,int,int,unsigned int) ; 

__attribute__((used)) static int i82975x_process_error_info(struct mem_ctl_info *mci,
		struct i82975x_error_info *info, int handle_errors)
{
	int row, chan;
	unsigned long offst, page;

	if (!(info->errsts2 & 0x0003))
		return 0;

	if (!handle_errors)
		return 1;

	if ((info->errsts ^ info->errsts2) & 0x0003) {
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, "UE overwrote CE", "");
		info->errsts = info->errsts2;
	}

	page = (unsigned long) info->eap;
	page >>= 1;
	if (info->xeap & 1)
		page |= 0x80000000;
	page >>= (PAGE_SHIFT - 1);
	row = edac_mc_find_csrow_by_page(mci, page);

	if (row == -1)	{
		i82975x_mc_printk(mci, KERN_ERR, "error processing EAP:\n"
			"\tXEAP=%u\n"
			"\t EAP=0x%08x\n"
			"\tPAGE=0x%08x\n",
			(info->xeap & 1) ? 1 : 0, info->eap, (unsigned int) page);
		return 0;
	}
	chan = (mci->csrows[row]->nr_channels == 1) ? 0 : info->eap & 1;
	offst = info->eap
			& ((1 << PAGE_SHIFT) -
			   (1 << mci->csrows[row]->channels[chan]->dimm->grain));

	if (info->errsts & 0x0002)
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     page, offst, 0,
				     row, -1, -1,
				     "i82975x UE", "");
	else
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
				     page, offst, info->derrsyn,
				     row, chan ? chan : 0, -1,
				     "i82975x CE", "");

	return 1;
}