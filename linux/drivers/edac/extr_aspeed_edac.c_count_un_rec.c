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
typedef  int u8 ;
typedef  int u32 ;
struct mem_ctl_info {struct csrow_info** csrows; } ;
struct csrow_info {int first_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_ERR_UNCORRECTED ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static void count_un_rec(struct mem_ctl_info *mci, u8 un_rec_cnt,
			 u32 un_rec_addr)
{
	struct csrow_info *csrow = mci->csrows[0];
	u32 page, offset, syndrome;

	if (!un_rec_cnt)
		return;

	/* report 1. error */
	/* note: un_rec_addr is the first unrecoverable error addr */
	page = un_rec_addr >> PAGE_SHIFT;
	offset = un_rec_addr & ~PAGE_MASK;
	/* syndrome is not available */
	syndrome = 0;
	edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
			     csrow->first_page + page, offset, syndrome,
			     0, 0, -1, "", "");

	/* report further errors (if there are) */
	/* note: no addresses are recorded */
	if (un_rec_cnt > 1) {
		/* page, offset and syndrome are not available */
		page = 0;
		offset = 0;
		syndrome = 0;
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, un_rec_cnt-1,
				     page, offset, syndrome, 0, 0, -1,
				     "address(es) not available", "");
	}
}