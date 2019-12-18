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
typedef  int (* elf_lookup_fn ) (int /*<<< orphan*/ ,scalar_t__,int,int*) ;
struct TYPE_2__ {int r_offset; int r_addend; int /*<<< orphan*/  r_info; } ;
typedef  int Elf_Word ;
typedef  scalar_t__ Elf_Size ;
typedef  TYPE_1__ Elf_Rela ;
typedef  int Elf_Addr ;

/* Variables and functions */
 int ELF64_R_TYPE_DATA (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF64_R_TYPE_ID (int /*<<< orphan*/ ) ; 
 int ELF_RELOC_RELA ; 
 scalar_t__ ELF_R_SYM (int /*<<< orphan*/ ) ; 
 scalar_t__ RELOC_BARE_SYMBOL (scalar_t__) ; 
 scalar_t__ RELOC_BASE_RELATIVE (scalar_t__) ; 
 scalar_t__ RELOC_PC_RELATIVE (scalar_t__) ; 
 scalar_t__ RELOC_RESOLVE_SYMBOL (scalar_t__) ; 
 int RELOC_TARGET_SIZE (scalar_t__) ; 
 scalar_t__ RELOC_UNALIGNED (scalar_t__) ; 
 int RELOC_VALUE_BITMASK (scalar_t__) ; 
 int RELOC_VALUE_RIGHTSHIFT (scalar_t__) ; 
 scalar_t__ R_SPARC_COPY ; 
 scalar_t__ R_SPARC_HIX22 ; 
 scalar_t__ R_SPARC_JMP_SLOT ; 
 scalar_t__ R_SPARC_LOX10 ; 
 scalar_t__ R_SPARC_NONE ; 
 scalar_t__ R_SPARC_OLO10 ; 
 scalar_t__ R_SPARC_RELATIVE ; 
 int elf_relocaddr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  reloc_target_bitmask ; 

int
elf_reloc(linker_file_t lf, Elf_Addr relocbase, const void *data, int type,
    elf_lookup_fn lookup)
{
	const Elf_Rela *rela;
	Elf_Word *where32;
	Elf_Addr *where;
	Elf_Size rtype, symidx;
	Elf_Addr value;
	Elf_Addr mask;
	Elf_Addr addr;
	int error;

	if (type != ELF_RELOC_RELA)
		return (-1);

	rela = (const Elf_Rela *)data;
	where = (Elf_Addr *)(relocbase + rela->r_offset);
	where32 = (Elf_Word *)where;
	rtype = ELF64_R_TYPE_ID(rela->r_info);
	symidx = ELF_R_SYM(rela->r_info);

	if (rtype == R_SPARC_NONE || rtype == R_SPARC_RELATIVE)
		return (0);

	if (rtype == R_SPARC_JMP_SLOT || rtype == R_SPARC_COPY ||
	    rtype >= nitems(reloc_target_bitmask)) {
		printf("kldload: unexpected relocation type %ld\n", rtype);
		return (-1);
	}

	if (RELOC_UNALIGNED(rtype)) {
		printf("kldload: unaligned relocation type %ld\n", rtype);
		return (-1);
	}

	value = rela->r_addend;

	if (RELOC_RESOLVE_SYMBOL(rtype)) {
		error = lookup(lf, symidx, 1, &addr);
		if (error != 0)
			return (-1);
		value += addr;
		if (RELOC_BARE_SYMBOL(rtype))
			value = elf_relocaddr(lf, value);
	}

	if (rtype == R_SPARC_OLO10)
		value = (value & 0x3ff) + ELF64_R_TYPE_DATA(rela->r_info);

	if (rtype == R_SPARC_HIX22)
		value ^= 0xffffffffffffffff;

	if (RELOC_PC_RELATIVE(rtype))
		value -= (Elf_Addr)where;

	if (RELOC_BASE_RELATIVE(rtype))
		value = elf_relocaddr(lf, value + relocbase);

	mask = RELOC_VALUE_BITMASK(rtype);
	value >>= RELOC_VALUE_RIGHTSHIFT(rtype);
	value &= mask;

	if (rtype == R_SPARC_LOX10)
		value |= 0x1c00;

	if (RELOC_TARGET_SIZE(rtype) > 32) {
		*where &= ~mask;
		*where |= value;
	} else {
		*where32 &= ~mask;
		*where32 |= value;
	}

	return (0);
}