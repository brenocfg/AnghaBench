#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  r_info; scalar_t__ r_offset; } ;
struct TYPE_20__ {scalar_t__ st_name; scalar_t__ st_value; int /*<<< orphan*/  st_info; } ;
struct TYPE_19__ {int /*<<< orphan*/  path; scalar_t__ strtab; scalar_t__ relocbase; scalar_t__ pltrela; scalar_t__ pltrel; } ;
struct TYPE_18__ {int /*<<< orphan*/  env; } ;
typedef  TYPE_1__ RtldLockState ;
typedef  TYPE_2__ Obj_Entry ;
typedef  TYPE_3__ Elf_Sym ;
typedef  int Elf_Size ;
typedef  TYPE_4__ Elf_Rel ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_R_SYM (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ STT_GNU_IFUNC ; 
 int /*<<< orphan*/  SYMLOOK_IN_PLT ; 
 int /*<<< orphan*/  basename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 TYPE_3__* find_symdef (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__ const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lock_release (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  lock_upgrade (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ reloc_jmpslot (scalar_t__*,scalar_t__,TYPE_2__ const*,TYPE_2__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  rlock_acquire (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rtld_bind_lock ; 
 int /*<<< orphan*/  rtld_die () ; 
 scalar_t__ rtld_resolve_ifunc (TYPE_2__ const*,TYPE_3__ const*) ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Elf_Addr
_rtld_bind(Obj_Entry *obj, Elf_Size reloff)
{
    const Elf_Rel *rel;
    const Elf_Sym *def;
    const Obj_Entry *defobj;
    Elf_Addr *where;
    Elf_Addr target;
    RtldLockState lockstate;

    rlock_acquire(rtld_bind_lock, &lockstate);
    if (sigsetjmp(lockstate.env, 0) != 0)
	    lock_upgrade(rtld_bind_lock, &lockstate);
    if (obj->pltrel)
	rel = (const Elf_Rel *)((const char *)obj->pltrel + reloff);
    else
	rel = (const Elf_Rel *)((const char *)obj->pltrela + reloff);

    where = (Elf_Addr *)(obj->relocbase + rel->r_offset);
    def = find_symdef(ELF_R_SYM(rel->r_info), obj, &defobj, SYMLOOK_IN_PLT,
	NULL, &lockstate);
    if (def == NULL)
	rtld_die();
    if (ELF_ST_TYPE(def->st_info) == STT_GNU_IFUNC)
	target = (Elf_Addr)rtld_resolve_ifunc(defobj, def);
    else
	target = (Elf_Addr)(defobj->relocbase + def->st_value);

    dbg("\"%s\" in \"%s\" ==> %p in \"%s\"",
      defobj->strtab + def->st_name, basename(obj->path),
      (void *)target, basename(defobj->path));

    /*
     * Write the new contents for the jmpslot. Note that depending on
     * architecture, the value which we need to return back to the
     * lazy binding trampoline may or may not be the target
     * address. The value returned from reloc_jmpslot() is the value
     * that the trampoline needs.
     */
    target = reloc_jmpslot(where, target, defobj, obj, rel);
    lock_release(rtld_bind_lock, &lockstate);
    return target;
}