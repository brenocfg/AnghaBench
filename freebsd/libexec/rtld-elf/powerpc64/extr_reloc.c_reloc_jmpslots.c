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
struct funcdesc {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  r_info; scalar_t__ r_offset; } ;
struct TYPE_12__ {scalar_t__ st_value; } ;
struct TYPE_11__ {int pltrelasize; int jmpslots_done; scalar_t__ relocbase; TYPE_3__* pltrela; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;
typedef  TYPE_2__ Elf_Sym ;
typedef  TYPE_3__ Elf_Rela ;
typedef  int /*<<< orphan*/  Elf_Rel ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_R_SYM (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF_R_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ R_PPC_JMP_SLOT ; 
 int SYMLOOK_IN_PLT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (scalar_t__*,int) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 TYPE_2__* find_symdef (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__ const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reloc_jmpslot (scalar_t__*,scalar_t__,TYPE_1__ const*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 TYPE_2__ const sym_zero ; 

int
reloc_jmpslots(Obj_Entry *obj, int flags, RtldLockState *lockstate)
{
	const Obj_Entry *defobj;
	const Elf_Rela *relalim;
	const Elf_Rela *rela;
	const Elf_Sym *def;
	Elf_Addr *where;
	Elf_Addr target;

	relalim = (const Elf_Rela *)((const char *)obj->pltrela +
	    obj->pltrelasize);
	for (rela = obj->pltrela; rela < relalim; rela++) {
		assert(ELF_R_TYPE(rela->r_info) == R_PPC_JMP_SLOT);
		where = (Elf_Addr *)(obj->relocbase + rela->r_offset);
		def = find_symdef(ELF_R_SYM(rela->r_info), obj, &defobj,
		    SYMLOOK_IN_PLT | flags, NULL, lockstate);
		if (def == NULL) {
			dbg("reloc_jmpslots: sym not found");
			return (-1);
		}

		target = (Elf_Addr)(defobj->relocbase + def->st_value);

		if (def == &sym_zero) {
			/* Zero undefined weak symbols */
#if !defined(_CALL_ELF) || _CALL_ELF == 1
			bzero(where, sizeof(struct funcdesc));
#else
			*where = 0;
#endif
		} else {
			reloc_jmpslot(where, target, defobj, obj,
			    (const Elf_Rel *) rela);
		}
	}

	obj->jmpslots_done = true;

	return (0);
}