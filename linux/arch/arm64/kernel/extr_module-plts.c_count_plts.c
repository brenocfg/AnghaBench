#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct plt_entry {int dummy; } ;
struct TYPE_10__ {int r_offset; int /*<<< orphan*/  r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  st_shndx; } ;
struct TYPE_8__ {int /*<<< orphan*/  sh_addralign; } ;
typedef  TYPE_1__ Elf_Shdr ;
typedef  int /*<<< orphan*/  Elf64_Word ;
typedef  TYPE_2__ Elf64_Sym ;
typedef  TYPE_3__ Elf64_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  ARM64_WORKAROUND_843419 ; 
 int /*<<< orphan*/  CONFIG_ARM64_ERRATUM_843419 ; 
 int /*<<< orphan*/  CONFIG_RANDOMIZE_BASE ; 
 scalar_t__ DIV_ROUND_UP (unsigned int,int) ; 
 int /*<<< orphan*/  ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
#define  R_AARCH64_ADR_PREL_PG_HI21 131 
#define  R_AARCH64_ADR_PREL_PG_HI21_NC 130 
#define  R_AARCH64_CALL26 129 
#define  R_AARCH64_JUMP26 128 
 int SZ_4K ; 
 scalar_t__ cpus_have_const_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  duplicate_rel (TYPE_3__*,int) ; 
 unsigned long long ffz (int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int count_plts(Elf64_Sym *syms, Elf64_Rela *rela, int num,
			       Elf64_Word dstidx, Elf_Shdr *dstsec)
{
	unsigned int ret = 0;
	Elf64_Sym *s;
	int i;

	for (i = 0; i < num; i++) {
		u64 min_align;

		switch (ELF64_R_TYPE(rela[i].r_info)) {
		case R_AARCH64_JUMP26:
		case R_AARCH64_CALL26:
			if (!IS_ENABLED(CONFIG_RANDOMIZE_BASE))
				break;

			/*
			 * We only have to consider branch targets that resolve
			 * to symbols that are defined in a different section.
			 * This is not simply a heuristic, it is a fundamental
			 * limitation, since there is no guaranteed way to emit
			 * PLT entries sufficiently close to the branch if the
			 * section size exceeds the range of a branch
			 * instruction. So ignore relocations against defined
			 * symbols if they live in the same section as the
			 * relocation target.
			 */
			s = syms + ELF64_R_SYM(rela[i].r_info);
			if (s->st_shndx == dstidx)
				break;

			/*
			 * Jump relocations with non-zero addends against
			 * undefined symbols are supported by the ELF spec, but
			 * do not occur in practice (e.g., 'jump n bytes past
			 * the entry point of undefined function symbol f').
			 * So we need to support them, but there is no need to
			 * take them into consideration when trying to optimize
			 * this code. So let's only check for duplicates when
			 * the addend is zero: this allows us to record the PLT
			 * entry address in the symbol table itself, rather than
			 * having to search the list for duplicates each time we
			 * emit one.
			 */
			if (rela[i].r_addend != 0 || !duplicate_rel(rela, i))
				ret++;
			break;
		case R_AARCH64_ADR_PREL_PG_HI21_NC:
		case R_AARCH64_ADR_PREL_PG_HI21:
			if (!IS_ENABLED(CONFIG_ARM64_ERRATUM_843419) ||
			    !cpus_have_const_cap(ARM64_WORKAROUND_843419))
				break;

			/*
			 * Determine the minimal safe alignment for this ADRP
			 * instruction: the section alignment at which it is
			 * guaranteed not to appear at a vulnerable offset.
			 *
			 * This comes down to finding the least significant zero
			 * bit in bits [11:3] of the section offset, and
			 * increasing the section's alignment so that the
			 * resulting address of this instruction is guaranteed
			 * to equal the offset in that particular bit (as well
			 * as all less signficant bits). This ensures that the
			 * address modulo 4 KB != 0xfff8 or 0xfffc (which would
			 * have all ones in bits [11:3])
			 */
			min_align = 2ULL << ffz(rela[i].r_offset | 0x7);

			/*
			 * Allocate veneer space for each ADRP that may appear
			 * at a vulnerable offset nonetheless. At relocation
			 * time, some of these will remain unused since some
			 * ADRP instructions can be patched to ADR instructions
			 * instead.
			 */
			if (min_align > SZ_4K)
				ret++;
			else
				dstsec->sh_addralign = max(dstsec->sh_addralign,
							   min_align);
			break;
		}
	}

	if (IS_ENABLED(CONFIG_ARM64_ERRATUM_843419) &&
	    cpus_have_const_cap(ARM64_WORKAROUND_843419))
		/*
		 * Add some slack so we can skip PLT slots that may trigger
		 * the erratum due to the placement of the ADRP instruction.
		 */
		ret += DIV_ROUND_UP(ret, (SZ_4K / sizeof(struct plt_entry)));

	return ret;
}