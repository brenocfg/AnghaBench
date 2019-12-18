#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  unsigned long u32 ;
struct TYPE_11__ {int toc_fixed; } ;
struct module {int /*<<< orphan*/  name; TYPE_1__ arch; } ;
struct TYPE_14__ {int r_offset; unsigned long r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_13__ {size_t sh_info; int sh_size; scalar_t__ sh_addr; } ;
struct TYPE_12__ {unsigned long st_value; int st_name; int /*<<< orphan*/  st_shndx; } ;
typedef  TYPE_2__ Elf64_Sym ;
typedef  TYPE_3__ Elf64_Shdr ;
typedef  TYPE_4__ Elf64_Rela ;

/* Variables and functions */
 int ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int ENOEXEC ; 
 int PPC_HA (unsigned long) ; 
 int PPC_INST_ADD ; 
 int PPC_INST_ADDI ; 
 int PPC_INST_ADDIS ; 
 int PPC_INST_LD ; 
 int PPC_LO (unsigned long) ; 
 int /*<<< orphan*/  R12 ; 
 int /*<<< orphan*/  R2 ; 
#define  R_PPC64_ADDR32 142 
#define  R_PPC64_ADDR64 141 
#define  R_PPC64_ENTRY 140 
#define  R_PPC64_REL16_HA 139 
#define  R_PPC64_REL16_LO 138 
#define  R_PPC64_REL32 137 
#define  R_PPC64_REL64 136 
#define  R_PPC64_TOC 135 
#define  R_PPC64_TOC16 134 
#define  R_PPC64_TOC16_DS 133 
#define  R_PPC64_TOC16_HA 132 
#define  R_PPC64_TOC16_LO 131 
#define  R_PPC64_TOC16_LO_DS 130 
#define  R_PPC64_TOCSAVE 129 
#define  R_PPC_REL24 128 
 int /*<<< orphan*/  SHN_LIVEPATCH ; 
 int /*<<< orphan*/  SHN_UNDEF ; 
 int __PPC_RA (int /*<<< orphan*/ ) ; 
 int __PPC_RB (int /*<<< orphan*/ ) ; 
 int __PPC_RT (int /*<<< orphan*/ ) ; 
 TYPE_2__* find_dot_toc (TYPE_3__*,char const*,unsigned int) ; 
 unsigned long local_entry_offset (TYPE_2__*) ; 
 unsigned long my_r2 (TYPE_3__*,struct module*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  restore_r2 (char const*,unsigned long*,struct module*) ; 
 int /*<<< orphan*/  squash_toc_save_inst (char const*,unsigned long) ; 
 unsigned long stub_for_addr (TYPE_3__*,unsigned long,struct module*) ; 

int apply_relocate_add(Elf64_Shdr *sechdrs,
		       const char *strtab,
		       unsigned int symindex,
		       unsigned int relsec,
		       struct module *me)
{
	unsigned int i;
	Elf64_Rela *rela = (void *)sechdrs[relsec].sh_addr;
	Elf64_Sym *sym;
	unsigned long *location;
	unsigned long value;

	pr_debug("Applying ADD relocate section %u to %u\n", relsec,
	       sechdrs[relsec].sh_info);

	/* First time we're called, we can fix up .TOC. */
	if (!me->arch.toc_fixed) {
		sym = find_dot_toc(sechdrs, strtab, symindex);
		/* It's theoretically possible that a module doesn't want a
		 * .TOC. so don't fail it just for that. */
		if (sym)
			sym->st_value = my_r2(sechdrs, me);
		me->arch.toc_fixed = true;
	}

	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rela); i++) {
		/* This is where to make the change */
		location = (void *)sechdrs[sechdrs[relsec].sh_info].sh_addr
			+ rela[i].r_offset;
		/* This is the symbol it is referring to */
		sym = (Elf64_Sym *)sechdrs[symindex].sh_addr
			+ ELF64_R_SYM(rela[i].r_info);

		pr_debug("RELOC at %p: %li-type as %s (0x%lx) + %li\n",
		       location, (long)ELF64_R_TYPE(rela[i].r_info),
		       strtab + sym->st_name, (unsigned long)sym->st_value,
		       (long)rela[i].r_addend);

		/* `Everything is relative'. */
		value = sym->st_value + rela[i].r_addend;

		switch (ELF64_R_TYPE(rela[i].r_info)) {
		case R_PPC64_ADDR32:
			/* Simply set it */
			*(u32 *)location = value;
			break;

		case R_PPC64_ADDR64:
			/* Simply set it */
			*(unsigned long *)location = value;
			break;

		case R_PPC64_TOC:
			*(unsigned long *)location = my_r2(sechdrs, me);
			break;

		case R_PPC64_TOC16:
			/* Subtract TOC pointer */
			value -= my_r2(sechdrs, me);
			if (value + 0x8000 > 0xffff) {
				pr_err("%s: bad TOC16 relocation (0x%lx)\n",
				       me->name, value);
				return -ENOEXEC;
			}
			*((uint16_t *) location)
				= (*((uint16_t *) location) & ~0xffff)
				| (value & 0xffff);
			break;

		case R_PPC64_TOC16_LO:
			/* Subtract TOC pointer */
			value -= my_r2(sechdrs, me);
			*((uint16_t *) location)
				= (*((uint16_t *) location) & ~0xffff)
				| (value & 0xffff);
			break;

		case R_PPC64_TOC16_DS:
			/* Subtract TOC pointer */
			value -= my_r2(sechdrs, me);
			if ((value & 3) != 0 || value + 0x8000 > 0xffff) {
				pr_err("%s: bad TOC16_DS relocation (0x%lx)\n",
				       me->name, value);
				return -ENOEXEC;
			}
			*((uint16_t *) location)
				= (*((uint16_t *) location) & ~0xfffc)
				| (value & 0xfffc);
			break;

		case R_PPC64_TOC16_LO_DS:
			/* Subtract TOC pointer */
			value -= my_r2(sechdrs, me);
			if ((value & 3) != 0) {
				pr_err("%s: bad TOC16_LO_DS relocation (0x%lx)\n",
				       me->name, value);
				return -ENOEXEC;
			}
			*((uint16_t *) location)
				= (*((uint16_t *) location) & ~0xfffc)
				| (value & 0xfffc);
			break;

		case R_PPC64_TOC16_HA:
			/* Subtract TOC pointer */
			value -= my_r2(sechdrs, me);
			value = ((value + 0x8000) >> 16);
			*((uint16_t *) location)
				= (*((uint16_t *) location) & ~0xffff)
				| (value & 0xffff);
			break;

		case R_PPC_REL24:
			/* FIXME: Handle weak symbols here --RR */
			if (sym->st_shndx == SHN_UNDEF ||
			    sym->st_shndx == SHN_LIVEPATCH) {
				/* External: go via stub */
				value = stub_for_addr(sechdrs, value, me);
				if (!value)
					return -ENOENT;
				if (!restore_r2(strtab + sym->st_name,
							(u32 *)location + 1, me))
					return -ENOEXEC;

				squash_toc_save_inst(strtab + sym->st_name, value);
			} else
				value += local_entry_offset(sym);

			/* Convert value to relative */
			value -= (unsigned long)location;
			if (value + 0x2000000 > 0x3ffffff || (value & 3) != 0){
				pr_err("%s: REL24 %li out of range!\n",
				       me->name, (long int)value);
				return -ENOEXEC;
			}

			/* Only replace bits 2 through 26 */
			*(uint32_t *)location
				= (*(uint32_t *)location & ~0x03fffffc)
				| (value & 0x03fffffc);
			break;

		case R_PPC64_REL64:
			/* 64 bits relative (used by features fixups) */
			*location = value - (unsigned long)location;
			break;

		case R_PPC64_REL32:
			/* 32 bits relative (used by relative exception tables) */
			/* Convert value to relative */
			value -= (unsigned long)location;
			if (value + 0x80000000 > 0xffffffff) {
				pr_err("%s: REL32 %li out of range!\n",
				       me->name, (long int)value);
				return -ENOEXEC;
			}
			*(u32 *)location = value;
			break;

		case R_PPC64_TOCSAVE:
			/*
			 * Marker reloc indicates we don't have to save r2.
			 * That would only save us one instruction, so ignore
			 * it.
			 */
			break;

		case R_PPC64_ENTRY:
			/*
			 * Optimize ELFv2 large code model entry point if
			 * the TOC is within 2GB range of current location.
			 */
			value = my_r2(sechdrs, me) - (unsigned long)location;
			if (value + 0x80008000 > 0xffffffff)
				break;
			/*
			 * Check for the large code model prolog sequence:
		         *	ld r2, ...(r12)
			 *	add r2, r2, r12
			 */
			if ((((uint32_t *)location)[0] & ~0xfffc) !=
			    (PPC_INST_LD | __PPC_RT(R2) | __PPC_RA(R12)))
				break;
			if (((uint32_t *)location)[1] !=
			    (PPC_INST_ADD | __PPC_RT(R2) | __PPC_RA(R2) | __PPC_RB(R12)))
				break;
			/*
			 * If found, replace it with:
			 *	addis r2, r12, (.TOC.-func)@ha
			 *	addi  r2,  r2, (.TOC.-func)@l
			 */
			((uint32_t *)location)[0] = PPC_INST_ADDIS | __PPC_RT(R2) |
						    __PPC_RA(R12) | PPC_HA(value);
			((uint32_t *)location)[1] = PPC_INST_ADDI | __PPC_RT(R2) |
						    __PPC_RA(R2) | PPC_LO(value);
			break;

		case R_PPC64_REL16_HA:
			/* Subtract location pointer */
			value -= (unsigned long)location;
			value = ((value + 0x8000) >> 16);
			*((uint16_t *) location)
				= (*((uint16_t *) location) & ~0xffff)
				| (value & 0xffff);
			break;

		case R_PPC64_REL16_LO:
			/* Subtract location pointer */
			value -= (unsigned long)location;
			*((uint16_t *) location)
				= (*((uint16_t *) location) & ~0xffff)
				| (value & 0xffff);
			break;

		default:
			pr_err("%s: Unknown ADD relocation: %lu\n",
			       me->name,
			       (unsigned long)ELF64_R_TYPE(rela[i].r_info));
			return -ENOEXEC;
		}
	}

	return 0;
}