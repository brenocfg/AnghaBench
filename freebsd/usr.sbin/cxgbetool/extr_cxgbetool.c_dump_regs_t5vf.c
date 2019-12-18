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
struct mod_regs {char* member_0; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 int dump_regs_table (int,char const**,int /*<<< orphan*/  const*,struct mod_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitems (struct mod_regs*) ; 
#define  t4vf_cim_regs 132 
#define  t4vf_mbdata_regs 131 
#define  t4vf_mps_regs 130 
#define  t5vf_pl_regs 129 
#define  t5vf_sge_regs 128 

__attribute__((used)) static int
dump_regs_t5vf(int argc, const char *argv[], const uint32_t *regs)
{
	static struct mod_regs t5vf_mod[] = {
		{ "sge", t5vf_sge_regs },
		{ "mps", t4vf_mps_regs },
		{ "pl", t5vf_pl_regs },
		{ "mbdata", t4vf_mbdata_regs },
		{ "cim", t4vf_cim_regs },
	};

	return dump_regs_table(argc, argv, regs, t5vf_mod, nitems(t5vf_mod));
}