#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int relsize; int relasize; int pltrelsize; int pltrelasize; int /*<<< orphan*/  pltrela; int /*<<< orphan*/  pltrel; int /*<<< orphan*/  rela; int /*<<< orphan*/  rel; int /*<<< orphan*/  relocbase; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ Obj_Entry ;
typedef  int /*<<< orphan*/  Elf_Rela ;
typedef  int /*<<< orphan*/  Elf_Rel ;

/* Variables and functions */
 int /*<<< orphan*/  dump_Elf_Rel (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_Elf_Rela (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtld_printf (char*,int,...) ; 

void
dump_obj_relocations (Obj_Entry *obj)
{

    rtld_printf("Object \"%s\", relocbase %p\n", obj->path, obj->relocbase);

    if (obj->relsize) {
        rtld_printf("Non-PLT Relocations: %ld\n",
            (obj->relsize / sizeof(Elf_Rel)));
        dump_Elf_Rel(obj, obj->rel, obj->relsize);
    }

    if (obj->relasize) {
        rtld_printf("Non-PLT Relocations with Addend: %ld\n",
            (obj->relasize / sizeof(Elf_Rela)));
        dump_Elf_Rela(obj, obj->rela, obj->relasize);
    }

    if (obj->pltrelsize) {
        rtld_printf("PLT Relocations: %ld\n",
            (obj->pltrelsize / sizeof(Elf_Rel)));
        dump_Elf_Rel(obj, obj->pltrel, obj->pltrelsize);
    }

    if (obj->pltrelasize) {
        rtld_printf("PLT Relocations with Addend: %ld\n",
            (obj->pltrelasize / sizeof(Elf_Rela)));
        dump_Elf_Rela(obj, obj->pltrela, obj->pltrelasize);
    }
}