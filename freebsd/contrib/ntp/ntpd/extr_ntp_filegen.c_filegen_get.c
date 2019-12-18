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
struct filegen_entry {char const* name; struct filegen_entry* next; int /*<<< orphan*/ * filegen; } ;
typedef  int /*<<< orphan*/  FILEGEN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 struct filegen_entry* filegen_registry ; 
 scalar_t__ strcmp (char const*,char const*) ; 

FILEGEN *
filegen_get(
	const char *	name
	)
{
	struct filegen_entry *f = filegen_registry;

	while (f) {
		if (f->name == name || strcmp(name, f->name) == 0) {
			DPRINTF(4, ("filegen_get(%s) = %p\n",
				    name, f->filegen));
			return f->filegen;
		}
		f = f->next;
	}
	DPRINTF(4, ("filegen_get(%s) = NULL\n", name));
	return NULL;
}