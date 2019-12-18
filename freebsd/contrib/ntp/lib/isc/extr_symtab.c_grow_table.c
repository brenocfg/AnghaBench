#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int size; unsigned int maxload; int /*<<< orphan*/ * table; int /*<<< orphan*/  mctx; int /*<<< orphan*/  case_sensitive; } ;
typedef  TYPE_1__ isc_symtab_t ;
typedef  int /*<<< orphan*/  eltlist_t ;
struct TYPE_10__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ elt_t ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 TYPE_2__* NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLINK (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 unsigned int hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * isc_mem_get (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
grow_table(isc_symtab_t *symtab) {
	eltlist_t *newtable;
	unsigned int i, newsize, newmax;

	REQUIRE(symtab != NULL);

	newsize = symtab->size * 2;
	newmax = newsize * 3 / 4;
	INSIST(newsize > 0U && newmax > 0U);

	newtable = isc_mem_get(symtab->mctx, newsize * sizeof(eltlist_t));
	if (newtable == NULL)
		return;

	for (i = 0; i < newsize; i++)
		INIT_LIST(newtable[i]);

	for (i = 0; i < symtab->size; i++) {
		elt_t *elt, *nelt;

		for (elt = HEAD(symtab->table[i]); elt != NULL; elt = nelt) {
			unsigned int hv;

			nelt = NEXT(elt, link);

			UNLINK(symtab->table[i], elt, link);
			hv = hash(elt->key, symtab->case_sensitive);
			APPEND(newtable[hv % newsize], elt, link);
		}
	}

	isc_mem_put(symtab->mctx, symtab->table,
		    symtab->size * sizeof(eltlist_t));

	symtab->table = newtable;
	symtab->size = newsize;
	symtab->maxload = newmax;
}