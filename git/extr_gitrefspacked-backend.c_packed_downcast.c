#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ref_store {TYPE_1__* be; } ;
struct packed_ref_store {unsigned int store_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,char const*,...) ; 
 TYPE_1__ refs_be_packed ; 

__attribute__((used)) static struct packed_ref_store *packed_downcast(struct ref_store *ref_store,
						unsigned int required_flags,
						const char *caller)
{
	struct packed_ref_store *refs;

	if (ref_store->be != &refs_be_packed)
		BUG("ref_store is type \"%s\" not \"packed\" in %s",
		    ref_store->be->name, caller);

	refs = (struct packed_ref_store *)ref_store;

	if ((refs->store_flags & required_flags) != required_flags)
		BUG("unallowed operation (%s), requires %x, has %x\n",
		    caller, required_flags, refs->store_flags);

	return refs;
}