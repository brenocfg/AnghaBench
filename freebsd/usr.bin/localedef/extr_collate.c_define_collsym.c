#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ collsym_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
 int /*<<< orphan*/ * RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  collsyms ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  new_pri () ; 
 int /*<<< orphan*/  stderr ; 

void
define_collsym(char *name)
{
	collsym_t	*sym;

	if ((sym = calloc(1, sizeof(*sym))) == NULL) {
		fprintf(stderr,"out of memory");
		return;
	}
	sym->name = name;
	sym->ref = new_pri();

	if (RB_FIND(collsyms, &collsyms, sym) != NULL) {
		/*
		 * This should never happen because we are only called
		 * for undefined symbols.
		 */
		free(sym);
		INTERR;
		return;
	}
	RB_INSERT(collsyms, &collsyms, sym);
}