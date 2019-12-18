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
struct ng_type {scalar_t__ version; int refs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ng_type*,int /*<<< orphan*/ ) ; 
 scalar_t__ NG_ABI_VERSION ; 
 size_t const NG_TYPESIZ ; 
 int /*<<< orphan*/  TRAP_ERROR () ; 
 int /*<<< orphan*/  TYPELIST_WLOCK () ; 
 int /*<<< orphan*/  TYPELIST_WUNLOCK () ; 
 int /*<<< orphan*/ * ng_findtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_typelist ; 
 int /*<<< orphan*/  printf (char*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  types ; 

int
ng_newtype(struct ng_type *tp)
{
	const size_t namelen = strlen(tp->name);

	/* Check version and type name fields */
	if ((tp->version != NG_ABI_VERSION) || (namelen == 0) ||
	    (namelen >= NG_TYPESIZ)) {
		TRAP_ERROR();
		if (tp->version != NG_ABI_VERSION) {
			printf("Netgraph: Node type rejected. ABI mismatch. "
			    "Suggest recompile\n");
		}
		return (EINVAL);
	}

	/* Check for name collision */
	if (ng_findtype(tp->name) != NULL) {
		TRAP_ERROR();
		return (EEXIST);
	}

	/* Link in new type */
	TYPELIST_WLOCK();
	LIST_INSERT_HEAD(&ng_typelist, tp, types);
	tp->refs = 1;	/* first ref is linked list */
	TYPELIST_WUNLOCK();
	return (0);
}