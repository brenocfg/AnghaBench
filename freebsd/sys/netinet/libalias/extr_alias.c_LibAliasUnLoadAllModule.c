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
struct proto_handler {int dummy; } ;
struct dll {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  LibAliasDetachHandlers (struct proto_handler*) ; 
 int /*<<< orphan*/  dlclose (int /*<<< orphan*/ ) ; 
 struct proto_handler* first_handler () ; 
 int /*<<< orphan*/  free (struct dll*) ; 
 struct dll* walk_dll_chain () ; 

int
LibAliasUnLoadAllModule(void)
{
	struct dll *t;
	struct proto_handler *p;

	/* Unload all modules then reload everything. */
	while ((p = first_handler()) != NULL) {	
		LibAliasDetachHandlers(p);
	}
	while ((t = walk_dll_chain()) != NULL) {	
		dlclose(t->handle);
		free(t);
	}
	return (1);
}