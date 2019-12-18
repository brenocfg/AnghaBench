#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct section {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  r_offset; int /*<<< orphan*/  r_info; } ;
struct TYPE_5__ {scalar_t__ st_shndx; } ;
typedef  TYPE_1__ Elf_Sym ;
typedef  TYPE_2__ Elf_Rel ;

/* Variables and functions */
 unsigned int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_386_16 133 
#define  R_386_32 132 
#define  R_386_NONE 131 
#define  R_386_PC16 130 
#define  R_386_PC32 129 
#define  R_386_PC8 128 
 scalar_t__ SHN_ABS ; 
 int /*<<< orphan*/  S_ABS ; 
 int /*<<< orphan*/  S_LIN ; 
 int /*<<< orphan*/  S_REL ; 
 int /*<<< orphan*/  S_SEG ; 
 int /*<<< orphan*/  add_reloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,char*,unsigned int,...) ; 
 scalar_t__ is_reloc (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  rel_type (unsigned int) ; 
 int /*<<< orphan*/  relocs16 ; 
 int /*<<< orphan*/  relocs32 ; 

__attribute__((used)) static int do_reloc_real(struct section *sec, Elf_Rel *rel, Elf_Sym *sym,
			 const char *symname)
{
	unsigned r_type = ELF32_R_TYPE(rel->r_info);
	int shn_abs = (sym->st_shndx == SHN_ABS) && !is_reloc(S_REL, symname);

	switch (r_type) {
	case R_386_NONE:
	case R_386_PC32:
	case R_386_PC16:
	case R_386_PC8:
		/*
		 * NONE can be ignored and PC relative relocations don't
		 * need to be adjusted.
		 */
		break;

	case R_386_16:
		if (shn_abs) {
			/*
			 * Whitelisted absolute symbols do not require
			 * relocation.
			 */
			if (is_reloc(S_ABS, symname))
				break;

			if (is_reloc(S_SEG, symname)) {
				add_reloc(&relocs16, rel->r_offset);
				break;
			}
		} else {
			if (!is_reloc(S_LIN, symname))
				break;
		}
		die("Invalid %s %s relocation: %s\n",
		    shn_abs ? "absolute" : "relative",
		    rel_type(r_type), symname);
		break;

	case R_386_32:
		if (shn_abs) {
			/*
			 * Whitelisted absolute symbols do not require
			 * relocation.
			 */
			if (is_reloc(S_ABS, symname))
				break;

			if (is_reloc(S_REL, symname)) {
				add_reloc(&relocs32, rel->r_offset);
				break;
			}
		} else {
			if (is_reloc(S_LIN, symname))
				add_reloc(&relocs32, rel->r_offset);
			break;
		}
		die("Invalid %s %s relocation: %s\n",
		    shn_abs ? "absolute" : "relative",
		    rel_type(r_type), symname);
		break;

	default:
		die("Unsupported relocation type: %s (%d)\n",
		    rel_type(r_type), r_type);
		break;
	}

	return 0;
}