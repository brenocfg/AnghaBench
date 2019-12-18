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
struct uasm_reloc {int* addr; int type; } ;
struct uasm_label {scalar_t__ addr; } ;

/* Variables and functions */
#define  R_MIPS_PC16 128 
 int build_bimm (long) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static inline void
__resolve_relocs(struct uasm_reloc *rel, struct uasm_label *lab)
{
	long laddr = (long)lab->addr;
	long raddr = (long)rel->addr;

	switch (rel->type) {
	case R_MIPS_PC16:
#ifdef CONFIG_CPU_LITTLE_ENDIAN
		*rel->addr |= (build_bimm(laddr - (raddr + 4)) << 16);
#else
		*rel->addr |= build_bimm(laddr - (raddr + 4));
#endif
		break;

	default:
		panic("Unsupported Micro-assembler relocation %d",
		      rel->type);
	}
}