#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  int (* elf_lookup_fn ) (int /*<<< orphan*/ ,int,int,int*) ;
struct TYPE_2__ {int r_addend; int /*<<< orphan*/  r_info; int /*<<< orphan*/  r_offset; } ;
typedef  int Elf_Word ;
typedef  TYPE_1__ Elf_Rela ;
typedef  int Elf_Half ;
typedef  int Elf_Addr ;

/* Variables and functions */
#define  ELF_RELOC_REL 134 
#define  ELF_RELOC_RELA 133 
 int ELF_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_PPC_ADDR16_HA 132 
#define  R_PPC_ADDR16_LO 131 
#define  R_PPC_ADDR32 130 
#define  R_PPC_NONE 129 
#define  R_PPC_RELATIVE 128 
 int elf_relocaddr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
elf_reloc_internal(linker_file_t lf, Elf_Addr relocbase, const void *data,
    int type, int local, elf_lookup_fn lookup)
{
	Elf_Addr *where;
	Elf_Half *hwhere;
	Elf_Addr addr;
	Elf_Addr addend;
	Elf_Word rtype, symidx;
	const Elf_Rela *rela;
	int error;

	switch (type) {
	case ELF_RELOC_REL:
		panic("PPC only supports RELA relocations");
		break;
	case ELF_RELOC_RELA:
		rela = (const Elf_Rela *)data;
		where = (Elf_Addr *) ((uintptr_t)relocbase + rela->r_offset);
		hwhere = (Elf_Half *) ((uintptr_t)relocbase + rela->r_offset);
		addend = rela->r_addend;
		rtype = ELF_R_TYPE(rela->r_info);
		symidx = ELF_R_SYM(rela->r_info);
		break;
	default:
		panic("elf_reloc: unknown relocation mode %d\n", type);
	}

	switch (rtype) {

	case R_PPC_NONE:
		break;

	case R_PPC_ADDR32: /* word32 S + A */
		error = lookup(lf, symidx, 1, &addr);
		if (error != 0)
			return -1;
		*where = elf_relocaddr(lf, addr + addend);
			break;

	case R_PPC_ADDR16_LO: /* #lo(S) */
		error = lookup(lf, symidx, 1, &addr);
		if (error != 0)
			return -1;
		/*
		 * addend values are sometimes relative to sections
		 * (i.e. .rodata) in rela, where in reality they
		 * are relative to relocbase. Detect this condition.
		 */
		if (addr > relocbase && addr <= (relocbase + addend))
			addr = relocbase;
		addr = elf_relocaddr(lf, addr + addend);
		*hwhere = addr & 0xffff;
		break;

	case R_PPC_ADDR16_HA: /* #ha(S) */
		error = lookup(lf, symidx, 1, &addr);
		if (error != 0)
			return -1;
		/*
		 * addend values are sometimes relative to sections
		 * (i.e. .rodata) in rela, where in reality they
		 * are relative to relocbase. Detect this condition.
		 */
		if (addr > relocbase && addr <= (relocbase + addend))
			addr = relocbase;
		addr = elf_relocaddr(lf, addr + addend);
		*hwhere = ((addr >> 16) + ((addr & 0x8000) ? 1 : 0))
		    & 0xffff;
		break;

	case R_PPC_RELATIVE: /* word32 B + A */
		*where = elf_relocaddr(lf, relocbase + addend);
		break;

	default:
		printf("kldload: unexpected relocation type %d\n",
		    (int) rtype);
		return -1;
	}
	return(0);
}