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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  cspi_regs ; 
 scalar_t__ dump_block_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  espi_regs ; 
 int /*<<< orphan*/  mc3_regs ; 
 int /*<<< orphan*/  mc4_regs ; 
 int /*<<< orphan*/  mc5_regs ; 
 int /*<<< orphan*/  pl_regs ; 
 int /*<<< orphan*/  rat_regs ; 
 int /*<<< orphan*/  sge_regs ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  tp_regs ; 
 int /*<<< orphan*/  tpi_regs ; 
 int /*<<< orphan*/  ulp_regs ; 

__attribute__((used)) static int
dump_regs_t2(int argc, char *argv[], int start_arg, uint32_t *regs)
{
	int match = 0;
	char *block_name = NULL;

	if (argc == start_arg + 1)
		block_name = argv[start_arg];
	else if (argc != start_arg)
		return -1;

	if (!block_name || !strcmp(block_name, "sge"))
		match += dump_block_regs(sge_regs, regs);
	if (!block_name || !strcmp(block_name, "mc3"))
		match += dump_block_regs(mc3_regs, regs);
	if (!block_name || !strcmp(block_name, "mc4"))
		match += dump_block_regs(mc4_regs, regs);
	if (!block_name || !strcmp(block_name, "tpi"))
		match += dump_block_regs(tpi_regs, regs);
	if (!block_name || !strcmp(block_name, "tp"))
		match += dump_block_regs(tp_regs, regs);
	if (!block_name || !strcmp(block_name, "rat"))
		match += dump_block_regs(rat_regs, regs);
	if (!block_name || !strcmp(block_name, "cspi"))
		match += dump_block_regs(cspi_regs, regs);
	if (!block_name || !strcmp(block_name, "espi"))
		match += dump_block_regs(espi_regs, regs);
	if (!block_name || !strcmp(block_name, "ulp"))
		match += dump_block_regs(ulp_regs, regs);
	if (!block_name || !strcmp(block_name, "pl"))
		match += dump_block_regs(pl_regs, regs);
	if (!block_name || !strcmp(block_name, "mc5"))
		match += dump_block_regs(mc5_regs, regs);
	if (!match)
		errx(1, "unknown block \"%s\"", block_name);
	return 0;
}