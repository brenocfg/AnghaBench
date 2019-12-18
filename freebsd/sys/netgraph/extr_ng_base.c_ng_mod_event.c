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
struct ng_type {int (* mod_event ) (int /*<<< orphan*/ ,int,void*) ;int refs; } ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ng_type* const,int /*<<< orphan*/ ) ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  TYPELIST_WLOCK () ; 
 int /*<<< orphan*/  TYPELIST_WUNLOCK () ; 
 int ng_newtype (struct ng_type* const) ; 
 int stub1 (int /*<<< orphan*/ ,int,void*) ; 
 int stub2 (int /*<<< orphan*/ ,int,void*) ; 
 int stub3 (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  types ; 

int
ng_mod_event(module_t mod, int event, void *data)
{
	struct ng_type *const type = data;
	int error = 0;

	switch (event) {
	case MOD_LOAD:

		/* Register new netgraph node type */
		if ((error = ng_newtype(type)) != 0)
			break;

		/* Call type specific code */
		if (type->mod_event != NULL)
			if ((error = (*type->mod_event)(mod, event, data))) {
				TYPELIST_WLOCK();
				type->refs--;	/* undo it */
				LIST_REMOVE(type, types);
				TYPELIST_WUNLOCK();
			}
		break;

	case MOD_UNLOAD:
		if (type->refs > 1) {		/* make sure no nodes exist! */
			error = EBUSY;
		} else {
			if (type->refs == 0) /* failed load, nothing to undo */
				break;
			if (type->mod_event != NULL) {	/* check with type */
				error = (*type->mod_event)(mod, event, data);
				if (error != 0)	/* type refuses.. */
					break;
			}
			TYPELIST_WLOCK();
			LIST_REMOVE(type, types);
			TYPELIST_WUNLOCK();
		}
		break;

	default:
		if (type->mod_event != NULL)
			error = (*type->mod_event)(mod, event, data);
		else
			error = EOPNOTSUPP;		/* XXX ? */
		break;
	}
	return (error);
}