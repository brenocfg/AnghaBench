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
struct pdc_pat_mem_phys_mem_location {int dimm_slot; } ;

/* Variables and functions */
 unsigned long PDT_ADDR_PERM_ERR ; 
 unsigned long PDT_ADDR_PHYS_MASK ; 
 unsigned long PDT_ADDR_SINGLE_ERR ; 
 scalar_t__ is_pdc_pat () ; 
 int /*<<< orphan*/  pdc_pat_mem_get_dimm_phys_location (struct pdc_pat_mem_phys_mem_location*,unsigned long) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned long,char*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void report_mem_err(unsigned long pde)
{
	struct pdc_pat_mem_phys_mem_location loc;
	unsigned long addr;
	char dimm_txt[32];

	addr = pde & PDT_ADDR_PHYS_MASK;

	/* show DIMM slot description on PAT machines */
	if (is_pdc_pat()) {
		pdc_pat_mem_get_dimm_phys_location(&loc, addr);
		sprintf(dimm_txt, "DIMM slot %02x, ", loc.dimm_slot);
	} else
		dimm_txt[0] = 0;

	pr_warn("PDT: BAD MEMORY at 0x%08lx, %s%s%s-bit error.\n",
		addr, dimm_txt,
		pde & PDT_ADDR_PERM_ERR ? "permanent ":"",
		pde & PDT_ADDR_SINGLE_ERR ? "single":"multi");
}