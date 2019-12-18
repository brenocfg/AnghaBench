#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  r_info; scalar_t__ r_offset; } ;
struct TYPE_13__ {int /*<<< orphan*/  st_info; } ;
struct TYPE_12__ {int gnu_ifunc; int pltrelasize; scalar_t__ relocbase; TYPE_3__* pltrela; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;
typedef  TYPE_2__ Elf_Sym ;
typedef  TYPE_3__ Elf_Rela ;
typedef  int /*<<< orphan*/  Elf_Rel ;
typedef  int /*<<< orphan*/  Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
#define  R_X86_64_JMP_SLOT 128 
 int /*<<< orphan*/  STT_GNU_IFUNC ; 
 int SYMLOOK_IN_PLT ; 
 TYPE_2__* find_symdef (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__ const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reloc_jmpslot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__ const*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rtld_bind_lock ; 
 int /*<<< orphan*/  rtld_resolve_ifunc (TYPE_1__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  wlock_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
reloc_gnu_ifunc(Obj_Entry *obj, int flags, RtldLockState *lockstate)
{
    const Elf_Rela *relalim;
    const Elf_Rela *rela;

    if (!obj->gnu_ifunc)
	return (0);
    relalim = (const Elf_Rela *)((const char *)obj->pltrela + obj->pltrelasize);
    for (rela = obj->pltrela;  rela < relalim;  rela++) {
	Elf_Addr *where, target;
	const Elf_Sym *def;
	const Obj_Entry *defobj;

	switch (ELF_R_TYPE(rela->r_info)) {
	case R_X86_64_JMP_SLOT:
	  where = (Elf_Addr *)(obj->relocbase + rela->r_offset);
	  def = find_symdef(ELF_R_SYM(rela->r_info), obj, &defobj,
		SYMLOOK_IN_PLT | flags, NULL, lockstate);
	  if (def == NULL)
	      return (-1);
	  if (ELF_ST_TYPE(def->st_info) != STT_GNU_IFUNC)
	      continue;
	  lock_release(rtld_bind_lock, lockstate);
	  target = (Elf_Addr)rtld_resolve_ifunc(defobj, def);
	  wlock_acquire(rtld_bind_lock, lockstate);
	  reloc_jmpslot(where, target, defobj, obj, (const Elf_Rel *)rela);
	  break;
	}
    }
    obj->gnu_ifunc = false;
    return (0);
}