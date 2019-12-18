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
typedef  int /*<<< orphan*/  isc_symvalue_t ;
typedef  int /*<<< orphan*/  isc_symtab_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ elt_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIND (int /*<<< orphan*/ *,char const*,unsigned int,unsigned int,TYPE_1__*) ; 
 int /*<<< orphan*/  ISC_R_NOTFOUND ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_SYMTAB (int /*<<< orphan*/ *) ; 

isc_result_t
isc_symtab_lookup(isc_symtab_t *symtab, const char *key, unsigned int type,
		  isc_symvalue_t *value)
{
	unsigned int bucket;
	elt_t *elt;

	REQUIRE(VALID_SYMTAB(symtab));
	REQUIRE(key != NULL);

	FIND(symtab, key, type, bucket, elt);

	if (elt == NULL)
		return (ISC_R_NOTFOUND);

	if (value != NULL)
		*value = elt->value;

	return (ISC_R_SUCCESS);
}