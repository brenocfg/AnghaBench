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
struct TYPE_3__ {int st_name; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ Elf_Sym ;

/* Variables and functions */
 int ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int STB_LOCAL ; 
 int STT_FUNC ; 
 scalar_t__ aflag ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ uflag ; 

__attribute__((used)) static bool
wantsym(const Elf_Sym *sym, const char *strtab)
{
    int type;
    int bind;

    type = ELF_ST_TYPE(sym->st_info);
    bind = ELF_ST_BIND(sym->st_info);

    if (type != STT_FUNC ||
      (aflag && bind == STB_LOCAL) ||
      (uflag && strchr(strtab + sym->st_name, '.') != NULL))
	return 0;

    return 1;
}