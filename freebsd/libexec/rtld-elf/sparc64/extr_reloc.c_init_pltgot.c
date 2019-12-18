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
struct TYPE_3__ {scalar_t__* pltgot; } ;
typedef  TYPE_1__ Obj_Entry ;
typedef  int /*<<< orphan*/  Elf_Word ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 scalar_t__ _rtld_bind_start_0 ; 
 scalar_t__ _rtld_bind_start_1 ; 
 int /*<<< orphan*/  install_plt (int /*<<< orphan*/ *,scalar_t__) ; 

void
init_pltgot(Obj_Entry *obj)
{
	Elf_Word *entry;

	if (obj->pltgot != NULL) {
		entry = (Elf_Word *)obj->pltgot;
		install_plt(&entry[0], (Elf_Addr)_rtld_bind_start_0);
		install_plt(&entry[8], (Elf_Addr)_rtld_bind_start_1);
		obj->pltgot[8] = (Elf_Addr)obj;
	}
}