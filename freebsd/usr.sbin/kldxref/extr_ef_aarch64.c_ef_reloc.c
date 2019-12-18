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
struct elf_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  r_info; scalar_t__ r_addend; scalar_t__ r_offset; } ;
typedef  int Elf_Size ;
typedef  TYPE_1__ Elf_Rela ;
typedef  scalar_t__ Elf_Off ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int EF_RELOC_RELA ; 
 int EINVAL ; 
 int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_AARCH64_ABS64 129 
#define  R_AARCH64_RELATIVE 128 
 int /*<<< orphan*/  warnx (char*,int) ; 

int
ef_reloc(struct elf_file *ef, const void *reldata, int reltype, Elf_Off relbase,
    Elf_Off dataoff, size_t len, void *dest)
{
	Elf_Addr *where, addend;
	Elf_Size rtype;
	const Elf_Rela *rela;

	if (reltype != EF_RELOC_RELA)
		return (EINVAL);

	rela = (const Elf_Rela *)reldata;
	where = (Elf_Addr *) ((Elf_Off)dest - dataoff + rela->r_offset);
	addend = rela->r_addend;
	rtype = ELF_R_TYPE(rela->r_info);

	if ((char *)where < (char *)dest || (char *)where >= (char *)dest + len)
		return (0);

	switch(rtype) {
	case R_AARCH64_RELATIVE:
		*where = relbase + addend;
		break;
	case R_AARCH64_ABS64:
		break;
	default:
		warnx("unhandled relocation type %lu", rtype);
		break;
	}
	return (0);
}