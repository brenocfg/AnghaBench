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
typedef  int (* elf_lookup_fn ) (int /*<<< orphan*/ ,int,int,scalar_t__*) ;
struct TYPE_2__ {int /*<<< orphan*/  r_info; scalar_t__ r_addend; scalar_t__ r_offset; } ;
typedef  int Elf_Word ;
typedef  TYPE_1__ Elf_Rela ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
#define  ELF_RELOC_REL 133 
#define  ELF_RELOC_RELA 132 
 int ELF_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_PPC64_ADDR64 131 
#define  R_PPC_JMP_SLOT 130 
#define  R_PPC_NONE 129 
#define  R_PPC_RELATIVE 128 
 scalar_t__ elf_relocaddr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
elf_reloc_internal(linker_file_t lf, Elf_Addr relocbase, const void *data,
    int type, int local, elf_lookup_fn lookup)
{
	Elf_Addr *where;
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
		where = (Elf_Addr *) (relocbase + rela->r_offset);
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

	case R_PPC64_ADDR64:	/* doubleword64 S + A */
		error = lookup(lf, symidx, 1, &addr);
		if (error != 0)
			return -1;
		addr += addend;
		*where = addr;
		break;

	case R_PPC_RELATIVE:	/* doubleword64 B + A */
		*where = elf_relocaddr(lf, relocbase + addend);
		break;

	case R_PPC_JMP_SLOT:	/* function descriptor copy */
		lookup(lf, symidx, 1, &addr);
#if !defined(_CALL_ELF) || _CALL_ELF == 1
		memcpy(where, (Elf_Addr *)addr, 3*sizeof(Elf_Addr));
#else
		*where = addr;
#endif
		__asm __volatile("dcbst 0,%0; sync" :: "r"(where) : "memory");
		break;

	default:
		printf("kldload: unexpected relocation type %d\n",
		    (int) rtype);
		return -1;
	}
	return(0);
}