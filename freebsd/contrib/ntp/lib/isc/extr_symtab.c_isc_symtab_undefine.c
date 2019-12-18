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
struct TYPE_9__ {int /*<<< orphan*/  count; int /*<<< orphan*/  mctx; int /*<<< orphan*/ * table; int /*<<< orphan*/  undefine_arg; int /*<<< orphan*/  (* undefine_action ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ isc_symtab_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_10__ {int /*<<< orphan*/  value; int /*<<< orphan*/  type; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ elt_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIND (TYPE_1__*,char const*,unsigned int,unsigned int,TYPE_2__*) ; 
 int /*<<< orphan*/  ISC_R_NOTFOUND ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLINK (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_SYMTAB (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

isc_result_t
isc_symtab_undefine(isc_symtab_t *symtab, const char *key, unsigned int type) {
	unsigned int bucket;
	elt_t *elt;

	REQUIRE(VALID_SYMTAB(symtab));
	REQUIRE(key != NULL);

	FIND(symtab, key, type, bucket, elt);

	if (elt == NULL)
		return (ISC_R_NOTFOUND);

	if (symtab->undefine_action != NULL)
		(symtab->undefine_action)(elt->key, elt->type,
					  elt->value, symtab->undefine_arg);
	UNLINK(symtab->table[bucket], elt, link);
	isc_mem_put(symtab->mctx, elt, sizeof(*elt));
	symtab->count--;

	return (ISC_R_SUCCESS);
}