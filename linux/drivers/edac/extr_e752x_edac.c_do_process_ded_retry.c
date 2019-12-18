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
typedef  int /*<<< orphan*/  u16 ;
struct mem_ctl_info {scalar_t__ pvt_info; } ;
struct e752x_pvt {scalar_t__ mc_symmetric; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  e752x_mc_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*,unsigned long,int) ; 
 int edac_mc_find_csrow_by_page (struct mem_ctl_info*,int) ; 

__attribute__((used)) static void do_process_ded_retry(struct mem_ctl_info *mci, u16 error,
				 u32 retry_add)
{
	u32 error_1b, page;
	int row;
	struct e752x_pvt *pvt = (struct e752x_pvt *)mci->pvt_info;

	error_1b = retry_add;
	page = error_1b >> (PAGE_SHIFT - 4);  /* convert the addr to 4k page */

	/* chip select are bits 14 & 13 */
	row = pvt->mc_symmetric ? ((page >> 1) & 3) :
		edac_mc_find_csrow_by_page(mci, page);

	e752x_mc_printk(mci, KERN_WARNING,
			"CE page 0x%lx, row %d : Memory read retry\n",
			(long unsigned int)page, row);
}