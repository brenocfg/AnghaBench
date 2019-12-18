#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct symsort_thunk {TYPE_1__* symtab; int /*<<< orphan*/  e; } ;
struct TYPE_5__ {scalar_t__ st_value; int /*<<< orphan*/  st_name; int /*<<< orphan*/  st_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  stridx; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ GElf_Sym ;

/* Variables and functions */
 int GELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int STB_LOCAL ; 
 char* elf_strptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelf_getsym (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int
symvalcmp(void *_thunk, const void *a1, const void *a2)
{
	GElf_Sym sym1, sym2;
	struct symsort_thunk *thunk;
	const char *s1, *s2;
	u_int i1, i2;
	int bind1, bind2;

	i1 = *(const u_int *)a1;
	i2 = *(const u_int *)a2;
	thunk = _thunk;

	(void)gelf_getsym(thunk->symtab->data, i1, &sym1);
	(void)gelf_getsym(thunk->symtab->data, i2, &sym2);

	if (sym1.st_value != sym2.st_value)
		return (sym1.st_value < sym2.st_value ? -1 : 1);

	/* Prefer non-local symbols. */
	bind1 = GELF_ST_BIND(sym1.st_info);
	bind2 = GELF_ST_BIND(sym2.st_info);
	if (bind1 != bind2) {
		if (bind1 == STB_LOCAL && bind2 != STB_LOCAL)
			return (-1);
		if (bind1 != STB_LOCAL && bind2 == STB_LOCAL)
			return (1);
	}

	s1 = elf_strptr(thunk->e, thunk->symtab->stridx, sym1.st_name);
	s2 = elf_strptr(thunk->e, thunk->symtab->stridx, sym2.st_name);
	if (s1 != NULL && s2 != NULL) {
		/* Prefer symbols without a leading '$'. */
		if (*s1 == '$')
			return (-1);
		if (*s2 == '$')
			return (1);

		/* Prefer symbols with fewer leading underscores. */
		for (; *s1 == '_' && *s2 == '_'; s1++, s2++)
			;
		if (*s1 == '_')
			return (-1);
		if (*s2 == '_')
			return (1);
	}

	return (0);
}