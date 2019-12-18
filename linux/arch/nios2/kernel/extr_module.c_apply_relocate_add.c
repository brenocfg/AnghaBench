#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct module {int /*<<< orphan*/  name; } ;
typedef  int int32_t ;
struct TYPE_7__ {int r_offset; int r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_6__ {size_t sh_info; int sh_size; scalar_t__ sh_addr; } ;
struct TYPE_5__ {int st_value; int st_name; } ;
typedef  TYPE_1__ Elf32_Sym ;
typedef  TYPE_2__ Elf32_Shdr ;
typedef  TYPE_3__ Elf32_Rela ;
typedef  int Elf32_Addr ;

/* Variables and functions */
 int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int ENOEXEC ; 
#define  R_NIOS2_BFD_RELOC_32 134 
#define  R_NIOS2_CALL26 133 
#define  R_NIOS2_HI16 132 
#define  R_NIOS2_HIADJ16 131 
#define  R_NIOS2_LO16 130 
#define  R_NIOS2_NONE 129 
#define  R_NIOS2_PCREL16 128 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 

int apply_relocate_add(Elf32_Shdr *sechdrs, const char *strtab,
			unsigned int symindex, unsigned int relsec,
			struct module *mod)
{
	unsigned int i;
	Elf32_Rela *rela = (void *)sechdrs[relsec].sh_addr;

	pr_debug("Applying relocate section %u to %u\n", relsec,
		 sechdrs[relsec].sh_info);

	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rela); i++) {
		/* This is where to make the change */
		uint32_t word;
		uint32_t *loc
			= ((void *)sechdrs[sechdrs[relsec].sh_info].sh_addr
			   + rela[i].r_offset);
		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		Elf32_Sym *sym
			= ((Elf32_Sym *)sechdrs[symindex].sh_addr
				+ ELF32_R_SYM(rela[i].r_info));
		uint32_t v = sym->st_value + rela[i].r_addend;

		pr_debug("reltype %d 0x%x name:<%s>\n",
			ELF32_R_TYPE(rela[i].r_info),
			rela[i].r_offset, strtab + sym->st_name);

		switch (ELF32_R_TYPE(rela[i].r_info)) {
		case R_NIOS2_NONE:
			break;
		case R_NIOS2_BFD_RELOC_32:
			*loc += v;
			break;
		case R_NIOS2_PCREL16:
			v -= (uint32_t)loc + 4;
			if ((int32_t)v > 0x7fff ||
				(int32_t)v < -(int32_t)0x8000) {
				pr_err("module %s: relocation overflow\n",
					mod->name);
				return -ENOEXEC;
			}
			word = *loc;
			*loc = ((((word >> 22) << 16) | (v & 0xffff)) << 6) |
				(word & 0x3f);
			break;
		case R_NIOS2_CALL26:
			if (v & 3) {
				pr_err("module %s: dangerous relocation\n",
					mod->name);
				return -ENOEXEC;
			}
			if ((v >> 28) != ((uint32_t)loc >> 28)) {
				pr_err("module %s: relocation overflow\n",
					mod->name);
				return -ENOEXEC;
			}
			*loc = (*loc & 0x3f) | ((v >> 2) << 6);
			break;
		case R_NIOS2_HI16:
			word = *loc;
			*loc = ((((word >> 22) << 16) |
				((v >> 16) & 0xffff)) << 6) | (word & 0x3f);
			break;
		case R_NIOS2_LO16:
			word = *loc;
			*loc = ((((word >> 22) << 16) | (v & 0xffff)) << 6) |
					(word & 0x3f);
			break;
		case R_NIOS2_HIADJ16:
			{
				Elf32_Addr word2;

				word = *loc;
				word2 = ((v >> 16) + ((v >> 15) & 1)) & 0xffff;
				*loc = ((((word >> 22) << 16) | word2) << 6) |
						(word & 0x3f);
			}
			break;

		default:
			pr_err("module %s: Unknown reloc: %u\n",
				mod->name, ELF32_R_TYPE(rela[i].r_info));
			return -ENOEXEC;
		}
	}

	return 0;
}