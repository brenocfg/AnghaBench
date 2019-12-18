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
typedef  scalar_t__ u32 ;
struct mem_ctl_info {scalar_t__ pvt_info; } ;
struct e752x_pvt {unsigned long tolm; unsigned long remapbase; scalar_t__ remaplimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  e752x_printk (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  edac_dbg (int,char*) ; 

__attribute__((used)) static unsigned long ctl_page_to_phys(struct mem_ctl_info *mci,
				unsigned long page)
{
	u32 remap;
	struct e752x_pvt *pvt = (struct e752x_pvt *)mci->pvt_info;

	edac_dbg(3, "\n");

	if (page < pvt->tolm)
		return page;

	if ((page >= 0x100000) && (page < pvt->remapbase))
		return page;

	remap = (page - pvt->tolm) + pvt->remapbase;

	if (remap < pvt->remaplimit)
		return remap;

	e752x_printk(KERN_ERR, "Invalid page %lx - out of range\n", page);
	return pvt->tolm - 1;
}