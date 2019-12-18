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
struct TYPE_6__ {scalar_t__ r_offset; } ;
struct TYPE_5__ {scalar_t__ glink; TYPE_2__ const* pltrela; scalar_t__ relocbase; } ;
typedef  TYPE_1__ Obj_Entry ;
typedef  TYPE_2__ Elf_Rela ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,void*,long,scalar_t__) ; 

__attribute__((used)) static int
reloc_plt_object(Obj_Entry *obj, const Elf_Rela *rela)
{
	Elf_Addr *where = (Elf_Addr *)(obj->relocbase + rela->r_offset);
	long reloff;

	reloff = rela - obj->pltrela;

	dbg(" reloc_plt_object: where=%p,reloff=%lx,glink=%#lx", (void *)where,
	    reloff, obj->glink);

#if !defined(_CALL_ELF) || _CALL_ELF == 1
	/* Glink code is 3 instructions after the first 32k, 2 before */
	*where = (Elf_Addr)obj->glink + 32 + 
	    8*((reloff < 0x8000) ? reloff : 0x8000) + 
	    12*((reloff < 0x8000) ? 0 : (reloff - 0x8000));
#else
	*where = (Elf_Addr)obj->glink + 4*reloff + 32;
#endif

	return (0);
}