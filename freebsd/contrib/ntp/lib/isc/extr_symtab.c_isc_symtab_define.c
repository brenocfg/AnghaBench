#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_symvalue_t ;
struct TYPE_11__ {scalar_t__ count; scalar_t__ maxload; int /*<<< orphan*/ * table; int /*<<< orphan*/  mctx; int /*<<< orphan*/  undefine_arg; int /*<<< orphan*/  (* undefine_action ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ isc_symtab_t ;
typedef  scalar_t__ isc_symexists_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_12__ {unsigned int type; int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ elt_t ;

/* Variables and functions */
 int /*<<< orphan*/  DE_CONST (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIND (TYPE_1__*,char const*,unsigned int,unsigned int,TYPE_2__*) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_LINK_INIT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_EXISTS ; 
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  PREPEND (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNLINK (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int VALID_SYMTAB (TYPE_1__*) ; 
 int /*<<< orphan*/  grow_table (TYPE_1__*) ; 
 scalar_t__ isc_mem_get (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isc_symexists_add ; 
 scalar_t__ isc_symexists_reject ; 
 scalar_t__ isc_symexists_replace ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

isc_result_t
isc_symtab_define(isc_symtab_t *symtab, const char *key, unsigned int type,
		  isc_symvalue_t value, isc_symexists_t exists_policy)
{
	unsigned int bucket;
	elt_t *elt;

	REQUIRE(VALID_SYMTAB(symtab));
	REQUIRE(key != NULL);
	REQUIRE(type != 0);

	FIND(symtab, key, type, bucket, elt);

	if (exists_policy != isc_symexists_add && elt != NULL) {
		if (exists_policy == isc_symexists_reject)
			return (ISC_R_EXISTS);
		INSIST(exists_policy == isc_symexists_replace);
		UNLINK(symtab->table[bucket], elt, link);
		if (symtab->undefine_action != NULL)
			(symtab->undefine_action)(elt->key, elt->type,
						  elt->value,
						  symtab->undefine_arg);
	} else {
		elt = (elt_t *)isc_mem_get(symtab->mctx, sizeof(*elt));
		if (elt == NULL)
			return (ISC_R_NOMEMORY);
		ISC_LINK_INIT(elt, link);
		symtab->count++;
	}

	/*
	 * Though the "key" can be const coming in, it is not stored as const
	 * so that the calling program can easily have writable access to
	 * it in its undefine_action function.  In the event that it *was*
	 * truly const coming in and then the caller modified it anyway ...
	 * well, don't do that!
	 */
	DE_CONST(key, elt->key);
	elt->type = type;
	elt->value = value;

	/*
	 * We prepend so that the most recent definition will be found.
	 */
	PREPEND(symtab->table[bucket], elt, link);

	if (symtab->count > symtab->maxload)
		grow_table(symtab);

	return (ISC_R_SUCCESS);
}