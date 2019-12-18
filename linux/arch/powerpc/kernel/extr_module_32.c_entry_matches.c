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
struct ppc_plt_entry {int* jump; } ;
typedef  int /*<<< orphan*/  Elf32_Addr ;

/* Variables and functions */
 int PPC_HA (int /*<<< orphan*/ ) ; 
 int PPC_INST_ADDI ; 
 int PPC_INST_ADDIS ; 
 int PPC_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R12 ; 
 int __PPC_RA (int /*<<< orphan*/ ) ; 
 int __PPC_RT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int entry_matches(struct ppc_plt_entry *entry, Elf32_Addr val)
{
	if (entry->jump[0] != (PPC_INST_ADDIS | __PPC_RT(R12) | PPC_HA(val)))
		return 0;
	if (entry->jump[1] != (PPC_INST_ADDI | __PPC_RT(R12) | __PPC_RA(R12) |
			       PPC_LO(val)))
		return 0;
	return 1;
}