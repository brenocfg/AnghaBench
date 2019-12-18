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
typedef  int u32 ;
struct mem_ctl_info {int /*<<< orphan*/  ctl_name; } ;
struct i82443bxgx_edacmc_error_info {int eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 int /*<<< orphan*/  HW_EVENT_ERR_UNCORRECTED ; 
 int I82443BXGX_EAP_OFFSET_MBE ; 
 int I82443BXGX_EAP_OFFSET_SBE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  edac_mc_find_csrow_by_page (struct mem_ctl_info*,int) ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int i82443bxgx_edacmc_process_error_info(struct mem_ctl_info *mci,
						struct
						i82443bxgx_edacmc_error_info
						*info, int handle_errors)
{
	int error_found = 0;
	u32 eapaddr, page, pageoffset;

	/* bits 30:12 hold the 4kb block in which the error occurred
	 * [p.61] */
	eapaddr = (info->eap & 0xfffff000);
	page = eapaddr >> PAGE_SHIFT;
	pageoffset = eapaddr - (page << PAGE_SHIFT);

	if (info->eap & I82443BXGX_EAP_OFFSET_SBE) {
		error_found = 1;
		if (handle_errors)
			edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
					     page, pageoffset, 0,
					     edac_mc_find_csrow_by_page(mci, page),
					     0, -1, mci->ctl_name, "");
	}

	if (info->eap & I82443BXGX_EAP_OFFSET_MBE) {
		error_found = 1;
		if (handle_errors)
			edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
					     page, pageoffset, 0,
					     edac_mc_find_csrow_by_page(mci, page),
					     0, -1, mci->ctl_name, "");
	}

	return error_found;
}