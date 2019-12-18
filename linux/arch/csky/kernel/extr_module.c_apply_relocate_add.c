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
struct TYPE_7__ {int r_offset; int r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_6__ {int sh_size; size_t sh_info; scalar_t__ sh_addr; } ;
struct TYPE_5__ {int st_value; } ;
typedef  TYPE_1__ Elf32_Sym ;
typedef  TYPE_2__ Elf32_Shdr ;
typedef  TYPE_3__ Elf32_Rela ;

/* Variables and functions */
 int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int ENOEXEC ; 
#define  R_CSKY_32 133 
#define  R_CSKY_ADDR_HI16 132 
#define  R_CSKY_ADDR_LO16 131 
#define  R_CSKY_PC32 130 
#define  R_CSKY_PCRELJSR_IMM11BY2 129 
#define  R_CSKY_PCRELJSR_IMM26BY2 128 
 int /*<<< orphan*/  jsri_2_lrw_jsr (int*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

int apply_relocate_add(Elf32_Shdr *sechdrs, const char *strtab,
		unsigned int symindex, unsigned int relsec, struct module *me)
{
	unsigned int i;
	Elf32_Rela	*rel = (void *) sechdrs[relsec].sh_addr;
	Elf32_Sym	*sym;
	uint32_t	*location;
	short		*temp;

	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rel); i++) {
		/* This is where to make the change */
		location = (void *)sechdrs[sechdrs[relsec].sh_info].sh_addr
							+ rel[i].r_offset;
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
						+ ELF32_R_SYM(rel[i].r_info);

		switch (ELF32_R_TYPE(rel[i].r_info)) {
		case R_CSKY_32:
			/* We add the value into the location given */
			*location = rel[i].r_addend + sym->st_value;
			break;
		case R_CSKY_PC32:
			/* Add the value, subtract its postition */
			*location = rel[i].r_addend + sym->st_value
							- (uint32_t)location;
			break;
		case R_CSKY_PCRELJSR_IMM11BY2:
			break;
		case R_CSKY_PCRELJSR_IMM26BY2:
			jsri_2_lrw_jsr(location);
			break;
		case R_CSKY_ADDR_HI16:
			temp = ((short  *)location) + 1;
			*temp = (short)
				((rel[i].r_addend + sym->st_value) >> 16);
			break;
		case R_CSKY_ADDR_LO16:
			temp = ((short  *)location) + 1;
			*temp = (short)
				((rel[i].r_addend + sym->st_value) & 0xffff);
			break;
		default:
			pr_err("module %s: Unknown relocation: %u\n",
				me->name, ELF32_R_TYPE(rel[i].r_info));
			return -ENOEXEC;
		}
	}
	return 0;
}