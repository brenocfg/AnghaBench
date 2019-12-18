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
struct vdso_elfinfo64 {int dynsymsize; scalar_t__ dynstr; TYPE_1__* dynsym; } ;
struct TYPE_3__ {scalar_t__ st_name; } ;
typedef  TYPE_1__ Elf64_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static Elf64_Sym *find_sym64(const struct vdso_elfinfo64 *e, const char *name)
{
	unsigned int i;

	for (i = 0; i < (e->dynsymsize / sizeof(Elf64_Sym)); i++) {
		Elf64_Sym *s = &e->dynsym[i];
		if (s->st_name == 0)
			continue;
		if (!strcmp(e->dynstr + s->st_name, name))
			return s;
	}
	return NULL;
}