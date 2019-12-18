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
typedef  int u_int ;
struct TYPE_6__ {scalar_t__ r_offset; } ;
struct TYPE_5__ {int pltrelasize; int* pltgot; scalar_t__ relocbase; int /*<<< orphan*/ * gotptr; TYPE_2__ const* pltrela; } ;
typedef  TYPE_1__ Obj_Entry ;
typedef  int Elf_Word ;
typedef  TYPE_2__ Elf_Rela ;
typedef  int Elf_Addr ;

/* Variables and functions */
 int JMPTAB_BASE (int) ; 
 int PLT_EXTENDED_BEGIN ; 
 int _ppc_ha (int*) ; 
 int _ppc_la (int*) ; 
 int /*<<< orphan*/  dbg (char*,void*,void*,int,int) ; 

__attribute__((used)) static int
reloc_plt_object(Obj_Entry *obj, const Elf_Rela *rela)
{
	Elf_Word *where = (Elf_Word *)(obj->relocbase + rela->r_offset);
	Elf_Addr *pltresolve, *pltlongresolve, *jmptab;
	Elf_Addr distance;
	int N = obj->pltrelasize / sizeof(Elf_Rela);
	int reloff;

	reloff = rela - obj->pltrela;

	if (reloff < 0)
		return (-1);

	if (obj->gotptr != NULL) {
		*where += (Elf_Addr)obj->relocbase;
		return (0);
	}

	pltlongresolve = obj->pltgot + 5;
	pltresolve = pltlongresolve + 5;

	distance = (Elf_Addr)pltresolve - (Elf_Addr)(where + 1);

	dbg(" reloc_plt_object: where=%p,pltres=%p,reloff=%x,distance=%x",
	    (void *)where, (void *)pltresolve, reloff, distance);

	if (reloff < PLT_EXTENDED_BEGIN) {
		/* li   r11,reloff  */
		/* b    pltresolve  */
		where[0] = 0x39600000 | reloff;
		where[1] = 0x48000000 | (distance & 0x03fffffc);
	} else {
		jmptab = obj->pltgot + JMPTAB_BASE(N);
		jmptab[reloff] = (u_int)pltlongresolve;

		/* lis	r11,jmptab[reloff]@ha */
		/* lwzu	r12,jmptab[reloff]@l(r11) */
		/* mtctr r12 */
		/* bctr */
		where[0] = 0x3d600000 | _ppc_ha(&jmptab[reloff]);
		where[1] = 0x858b0000 | _ppc_la(&jmptab[reloff]);
		where[2] = 0x7d8903a6;
		where[3] = 0x4e800420;
	}
		

	/*
	 * The icache will be sync'd in reloc_plt, which is called
	 * after all the slots have been updated
	 */

	return (0);
}