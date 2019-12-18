#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_10__ {scalar_t__ st_value; scalar_t__ st_shndx; } ;
struct TYPE_9__ {scalar_t__ tlsoffset; int /*<<< orphan*/  tlsindex; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;
typedef  TYPE_2__ Elf_Sym ;
typedef  TYPE_3__ Elf_Rela ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 scalar_t__ ELF_R_SYM (int /*<<< orphan*/ ) ; 
 scalar_t__ SHN_UNDEF ; 
 scalar_t__ _rtld_tlsdesc_dynamic ; 
 scalar_t__ _rtld_tlsdesc_static ; 
 scalar_t__ _rtld_tlsdesc_undef ; 
 TYPE_2__* find_symdef (scalar_t__,TYPE_1__ const*,TYPE_1__ const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ reloc_tlsdesc_alloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rtld_die () ; 

__attribute__((used)) static void
reloc_tlsdesc(const Obj_Entry *obj, const Elf_Rela *rela, Elf_Addr *where,
    int flags, RtldLockState *lockstate)
{
	const Elf_Sym *def;
	const Obj_Entry *defobj;
	Elf_Addr offs;


	offs = 0;
	if (ELF_R_SYM(rela->r_info) != 0) {
		def = find_symdef(ELF_R_SYM(rela->r_info), obj, &defobj, flags,
			    NULL, lockstate);
		if (def == NULL)
			rtld_die();
		offs = def->st_value;
		obj = defobj;
		if (def->st_shndx == SHN_UNDEF) {
			/* Weak undefined thread variable */
			where[0] = (Elf_Addr)_rtld_tlsdesc_undef;
			where[1] = rela->r_addend;
			return;
		}
	}
	offs += rela->r_addend;

	if (obj->tlsoffset != 0) {
		/* Variable is in initialy allocated TLS segment */
		where[0] = (Elf_Addr)_rtld_tlsdesc_static;
		where[1] = obj->tlsoffset + offs;
	} else {
		/* TLS offest is unknown at load time, use dynamic resolving */
		where[0] = (Elf_Addr)_rtld_tlsdesc_dynamic;
		where[1] = reloc_tlsdesc_alloc(obj->tlsindex, offs);
	}
}