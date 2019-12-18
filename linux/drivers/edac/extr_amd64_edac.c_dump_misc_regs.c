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
struct amd64_pvt {int /*<<< orphan*/  ecc_sym_sz; scalar_t__ umc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dump_misc_regs (struct amd64_pvt*) ; 
 int /*<<< orphan*/  __dump_misc_regs_df (struct amd64_pvt*) ; 
 int /*<<< orphan*/  amd64_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dhar_valid (struct amd64_pvt*) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,char*) ; 

__attribute__((used)) static void dump_misc_regs(struct amd64_pvt *pvt)
{
	if (pvt->umc)
		__dump_misc_regs_df(pvt);
	else
		__dump_misc_regs(pvt);

	edac_dbg(1, "  DramHoleValid: %s\n", dhar_valid(pvt) ? "yes" : "no");

	amd64_info("using x%u syndromes.\n", pvt->ecc_sym_sz);
}