#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_symtabaction_t ;
struct TYPE_4__ {unsigned int size; unsigned int maxload; int /*<<< orphan*/  magic; int /*<<< orphan*/  case_sensitive; void* undefine_arg; int /*<<< orphan*/  undefine_action; scalar_t__ count; int /*<<< orphan*/ * mctx; int /*<<< orphan*/ * table; } ;
typedef  TYPE_1__ isc_symtab_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;
typedef  int /*<<< orphan*/  eltlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  SYMTAB_MAGIC ; 
 scalar_t__ isc_mem_get (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

isc_result_t
isc_symtab_create(isc_mem_t *mctx, unsigned int size,
		  isc_symtabaction_t undefine_action,
		  void *undefine_arg,
		  isc_boolean_t case_sensitive,
		  isc_symtab_t **symtabp)
{
	isc_symtab_t *symtab;
	unsigned int i;

	REQUIRE(mctx != NULL);
	REQUIRE(symtabp != NULL && *symtabp == NULL);
	REQUIRE(size > 0);	/* Should be prime. */

	symtab = (isc_symtab_t *)isc_mem_get(mctx, sizeof(*symtab));
	if (symtab == NULL)
		return (ISC_R_NOMEMORY);
	symtab->table = (eltlist_t *)isc_mem_get(mctx,
						 size * sizeof(eltlist_t));
	if (symtab->table == NULL) {
		isc_mem_put(mctx, symtab, sizeof(*symtab));
		return (ISC_R_NOMEMORY);
	}
	for (i = 0; i < size; i++)
		INIT_LIST(symtab->table[i]);
	symtab->mctx = mctx;
	symtab->size = size;
	symtab->count = 0;
	symtab->maxload = size * 3 / 4;
	symtab->undefine_action = undefine_action;
	symtab->undefine_arg = undefine_arg;
	symtab->case_sensitive = case_sensitive;
	symtab->magic = SYMTAB_MAGIC;

	*symtabp = symtab;

	return (ISC_R_SUCCESS);
}