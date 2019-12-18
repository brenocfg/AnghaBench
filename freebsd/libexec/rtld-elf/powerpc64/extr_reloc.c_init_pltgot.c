#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct funcdesc {int dummy; } ;
struct TYPE_3__ {scalar_t__* pltgot; } ;
typedef  TYPE_1__ Obj_Entry ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  _rtld_bind_start ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

void
init_pltgot(Obj_Entry *obj)
{
	Elf_Addr *pltcall;

	pltcall = obj->pltgot;

	if (pltcall == NULL) {
		return;
	}

#if defined(_CALL_ELF) && _CALL_ELF == 2
	pltcall[0] = (Elf_Addr)&_rtld_bind_start; 
	pltcall[1] = (Elf_Addr)obj;
#else
	memcpy(pltcall, _rtld_bind_start, sizeof(struct funcdesc));
	pltcall[2] = (Elf_Addr)obj;
#endif
}