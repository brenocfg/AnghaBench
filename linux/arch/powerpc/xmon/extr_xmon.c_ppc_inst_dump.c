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

/* Variables and functions */
 int generic_inst_dump (unsigned long,long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_insn_powerpc ; 

__attribute__((used)) static int
ppc_inst_dump(unsigned long adr, long count, int praddr)
{
	return generic_inst_dump(adr, count, praddr, print_insn_powerpc);
}