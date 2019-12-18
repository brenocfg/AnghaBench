#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  r_info; scalar_t__ r_offset; } ;
struct TYPE_12__ {scalar_t__ st_value; int /*<<< orphan*/  st_info; } ;
struct TYPE_11__ {int jmpslots_done; int pltrelsize; int gnu_ifunc; scalar_t__ relocbase; TYPE_3__* pltrel; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;
typedef  TYPE_2__ Elf_Sym ;
typedef  TYPE_3__ Elf_Rel ;
typedef  int /*<<< orphan*/  Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
#define  R_386_IRELATIVE 129 
#define  R_386_JMP_SLOT 128 
 int /*<<< orphan*/  STT_GNU_IFUNC ; 
 int SYMLOOK_IN_PLT ; 
 int /*<<< orphan*/  _rtld_error (char*,int) ; 
 TYPE_2__* find_symdef (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__ const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reloc_jmpslot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__ const*,TYPE_1__*,TYPE_3__ const*) ; 

int
reloc_jmpslots(Obj_Entry *obj, int flags, RtldLockState *lockstate)
{
    const Elf_Rel *rellim;
    const Elf_Rel *rel;

    if (obj->jmpslots_done)
	return 0;
    rellim = (const Elf_Rel *)((const char *)obj->pltrel + obj->pltrelsize);
    for (rel = obj->pltrel;  rel < rellim;  rel++) {
	Elf_Addr *where, target;
	const Elf_Sym *def;
	const Obj_Entry *defobj;

	switch (ELF_R_TYPE(rel->r_info)) {
	case R_386_JMP_SLOT:
	  where = (Elf_Addr *)(obj->relocbase + rel->r_offset);
	  def = find_symdef(ELF_R_SYM(rel->r_info), obj, &defobj,
		SYMLOOK_IN_PLT | flags, NULL, lockstate);
	  if (def == NULL)
	      return (-1);
	  if (ELF_ST_TYPE(def->st_info) == STT_GNU_IFUNC) {
	      obj->gnu_ifunc = true;
	      continue;
	  }
	  target = (Elf_Addr)(defobj->relocbase + def->st_value);
	  reloc_jmpslot(where, target, defobj, obj, rel);
	  break;

	case R_386_IRELATIVE:
	  break;

	default:
	  _rtld_error("Unknown relocation type %x in PLT",
	    ELF_R_TYPE(rel->r_info));
	  return (-1);
	}
    }

    obj->jmpslots_done = true;
    return 0;
}