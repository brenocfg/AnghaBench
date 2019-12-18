#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct filegen_entry {char const* name; int /*<<< orphan*/ * filegen; struct filegen_entry* next; } ;
typedef  int /*<<< orphan*/  FILEGEN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 struct filegen_entry* emalloc (int) ; 
 char const* estrdup (char const*) ; 
 int /*<<< orphan*/  filegen_init (char const*,char const*,int /*<<< orphan*/ *) ; 
 struct filegen_entry* filegen_registry ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

void
filegen_register(
	const char *	dir,
	const char *	name,
	FILEGEN *	filegen
	)
{
	struct filegen_entry **ppfe;

	DPRINTF(4, ("filegen_register(%s, %p)\n", name, filegen));

	filegen_init(dir, name, filegen);

	ppfe = &filegen_registry;
	while (NULL != *ppfe) {
		if ((*ppfe)->name == name 
		    || !strcmp((*ppfe)->name, name)) {

			DPRINTF(5, ("replacing filegen %p\n",
				    (*ppfe)->filegen));

			(*ppfe)->filegen = filegen;
			return;
		}
		ppfe = &((*ppfe)->next);
	}

	*ppfe = emalloc(sizeof **ppfe);

	(*ppfe)->next = NULL;
	(*ppfe)->name = estrdup(name);
	(*ppfe)->filegen = filegen;

	DPRINTF(6, ("adding new filegen\n"));
	
	return;
}