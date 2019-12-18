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
struct object_id {int dummy; } ;
struct object_entry {int preferred_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  nr_result ; 
 struct object_entry* packlist_find (int /*<<< orphan*/ *,struct object_id const*) ; 
 int /*<<< orphan*/  to_pack ; 

__attribute__((used)) static int have_duplicate_entry(const struct object_id *oid,
				int exclude)
{
	struct object_entry *entry;

	entry = packlist_find(&to_pack, oid);
	if (!entry)
		return 0;

	if (exclude) {
		if (!entry->preferred_base)
			nr_result--;
		entry->preferred_base = 1;
	}

	return 1;
}