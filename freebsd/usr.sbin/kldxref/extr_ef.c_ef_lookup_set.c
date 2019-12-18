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
typedef  int /*<<< orphan*/  elf_file_t ;
struct TYPE_3__ {long st_value; } ;
typedef  TYPE_1__ Elf_Sym ;

/* Variables and functions */
 int ef_lookup_symbol (int /*<<< orphan*/ ,char*,TYPE_1__**) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
ef_lookup_set(elf_file_t ef, const char *name, long *startp, long *stopp,
    long *countp)
{
	Elf_Sym *sym;
	char *setsym;
	int error, len;

	len = strlen(name) + sizeof("__start_set_"); /* sizeof includes \0 */
	setsym = malloc(len);
	if (setsym == NULL)
		return (errno);

	/* get address of first entry */
	snprintf(setsym, len, "%s%s", "__start_set_", name);
	error = ef_lookup_symbol(ef, setsym, &sym);
	if (error != 0)
		goto out;
	*startp = sym->st_value;

	/* get address of last entry */
	snprintf(setsym, len, "%s%s", "__stop_set_", name);
	error = ef_lookup_symbol(ef, setsym, &sym);
	if (error != 0)
		goto out;
	*stopp = sym->st_value;

	/* and the number of entries */
	*countp = (*stopp - *startp) / sizeof(void *);

out:
	free(setsym);
	return (error);
}