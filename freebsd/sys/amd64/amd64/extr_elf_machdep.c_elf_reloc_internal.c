#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  int (* elf_lookup_fn ) (int /*<<< orphan*/ ,int,int,scalar_t__*) ;
struct TYPE_4__ {int /*<<< orphan*/  r_info; scalar_t__ r_offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  r_info; scalar_t__ r_addend; scalar_t__ r_offset; } ;
typedef  int Elf_Size ;
typedef  TYPE_1__ Elf_Rela ;
typedef  TYPE_2__ Elf_Rel ;
typedef  scalar_t__ Elf_Addr ;
typedef  scalar_t__ Elf64_Addr ;
typedef  scalar_t__ Elf32_Addr ;

/* Variables and functions */
#define  ELF_RELOC_REL 139 
#define  ELF_RELOC_RELA 138 
 int ELF_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_X86_64_32S 137 
#define  R_X86_64_64 136 
#define  R_X86_64_COPY 135 
#define  R_X86_64_GLOB_DAT 134 
#define  R_X86_64_IRELATIVE 133 
#define  R_X86_64_JMP_SLOT 132 
#define  R_X86_64_NONE 131 
#define  R_X86_64_PC32 130 
#define  R_X86_64_PLT32 129 
#define  R_X86_64_RELATIVE 128 
 scalar_t__ elf_relocaddr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ stub1 () ; 

__attribute__((used)) static int
elf_reloc_internal(linker_file_t lf, Elf_Addr relocbase, const void *data,
    int type, elf_lookup_fn lookup)
{
	Elf64_Addr *where, val;
	Elf32_Addr *where32, val32;
	Elf_Addr addr;
	Elf_Addr addend;
	Elf_Size rtype, symidx;
	const Elf_Rel *rel;
	const Elf_Rela *rela;
	int error;

	switch (type) {
	case ELF_RELOC_REL:
		rel = (const Elf_Rel *)data;
		where = (Elf_Addr *) (relocbase + rel->r_offset);
		rtype = ELF_R_TYPE(rel->r_info);
		symidx = ELF_R_SYM(rel->r_info);
		/* Addend is 32 bit on 32 bit relocs */
		switch (rtype) {
		case R_X86_64_PC32:
		case R_X86_64_32S:
		case R_X86_64_PLT32:
			addend = *(Elf32_Addr *)where;
			break;
		default:
			addend = *where;
			break;
		}
		break;
	case ELF_RELOC_RELA:
		rela = (const Elf_Rela *)data;
		where = (Elf_Addr *) (relocbase + rela->r_offset);
		addend = rela->r_addend;
		rtype = ELF_R_TYPE(rela->r_info);
		symidx = ELF_R_SYM(rela->r_info);
		break;
	default:
		panic("unknown reloc type %d\n", type);
	}

	switch (rtype) {
		case R_X86_64_NONE:	/* none */
			break;

		case R_X86_64_64:		/* S + A */
			error = lookup(lf, symidx, 1, &addr);
			val = addr + addend;
			if (error != 0)
				return -1;
			if (*where != val)
				*where = val;
			break;

		case R_X86_64_PC32:	/* S + A - P */
		case R_X86_64_PLT32:	/* L + A - P, L is PLT location for
					   the symbol, which we treat as S */
			error = lookup(lf, symidx, 1, &addr);
			where32 = (Elf32_Addr *)where;
			val32 = (Elf32_Addr)(addr + addend - (Elf_Addr)where);
			if (error != 0)
				return -1;
			if (*where32 != val32)
				*where32 = val32;
			break;

		case R_X86_64_32S:	/* S + A sign extend */
			error = lookup(lf, symidx, 1, &addr);
			val32 = (Elf32_Addr)(addr + addend);
			where32 = (Elf32_Addr *)where;
			if (error != 0)
				return -1;
			if (*where32 != val32)
				*where32 = val32;
			break;

		case R_X86_64_COPY:	/* none */
			/*
			 * There shouldn't be copy relocations in kernel
			 * objects.
			 */
			printf("kldload: unexpected R_COPY relocation\n");
			return (-1);

		case R_X86_64_GLOB_DAT:	/* S */
		case R_X86_64_JMP_SLOT:	/* XXX need addend + offset */
			error = lookup(lf, symidx, 1, &addr);
			if (error != 0)
				return -1;
			if (*where != addr)
				*where = addr;
			break;

		case R_X86_64_RELATIVE:	/* B + A */
			addr = elf_relocaddr(lf, relocbase + addend);
			val = addr;
			if (*where != val)
				*where = val;
			break;

		case R_X86_64_IRELATIVE:
			addr = relocbase + addend;
			val = ((Elf64_Addr (*)(void))addr)();
			if (*where != val)
				*where = val;
			break;

		default:
			printf("kldload: unexpected relocation type %ld\n",
			       rtype);
			return (-1);
	}
	return (0);
}