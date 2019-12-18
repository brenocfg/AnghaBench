#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  r_info; scalar_t__ r_offset; } ;
struct TYPE_6__ {int pltrelasize; int irelative; scalar_t__ relocbase; TYPE_2__* pltrela; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;
typedef  TYPE_2__ Elf_Rela ;
typedef  int /*<<< orphan*/  Elf_Addr ;

/* Variables and functions */
 int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_AARCH64_IRELATIVE 131 
#define  R_AARCH64_JUMP_SLOT 130 
#define  R_AARCH64_NONE 129 
#define  R_AARCH64_TLSDESC 128 
 int SYMLOOK_IN_PLT ; 
 int /*<<< orphan*/  _rtld_error (char*,unsigned int) ; 
 int /*<<< orphan*/  reloc_tlsdesc (TYPE_1__*,TYPE_2__ const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
reloc_plt(Obj_Entry *obj, int flags, RtldLockState *lockstate)
{
	const Elf_Rela *relalim;
	const Elf_Rela *rela;

	relalim = (const Elf_Rela *)((const char *)obj->pltrela +
	    obj->pltrelasize);
	for (rela = obj->pltrela; rela < relalim; rela++) {
		Elf_Addr *where;

		where = (Elf_Addr *)(obj->relocbase + rela->r_offset);

		switch(ELF_R_TYPE(rela->r_info)) {
		case R_AARCH64_JUMP_SLOT:
			*where += (Elf_Addr)obj->relocbase;
			break;
		case R_AARCH64_TLSDESC:
			reloc_tlsdesc(obj, rela, where, SYMLOOK_IN_PLT | flags,
			    lockstate);
			break;
		case R_AARCH64_IRELATIVE:
			obj->irelative = true;
			break;
		case R_AARCH64_NONE:
			break;
		default:
			_rtld_error("Unknown relocation type %u in PLT",
			    (unsigned int)ELF_R_TYPE(rela->r_info));
			return (-1);
		}
	}

	return (0);
}