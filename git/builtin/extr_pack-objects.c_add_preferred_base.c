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
struct TYPE_2__ {unsigned long tree_size; void* tree_data; int /*<<< orphan*/  oid; } ;
struct pbase_tree {TYPE_1__ pcache; struct pbase_tree* next; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  num_preferred_base ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,struct object_id*) ; 
 struct pbase_tree* pbase_tree ; 
 void* read_object_with_reference (int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ ,unsigned long*,struct object_id*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  tree_type ; 
 scalar_t__ window ; 
 struct pbase_tree* xcalloc (int,int) ; 

__attribute__((used)) static void add_preferred_base(struct object_id *oid)
{
	struct pbase_tree *it;
	void *data;
	unsigned long size;
	struct object_id tree_oid;

	if (window <= num_preferred_base++)
		return;

	data = read_object_with_reference(the_repository, oid,
					  tree_type, &size, &tree_oid);
	if (!data)
		return;

	for (it = pbase_tree; it; it = it->next) {
		if (oideq(&it->pcache.oid, &tree_oid)) {
			free(data);
			return;
		}
	}

	it = xcalloc(1, sizeof(*it));
	it->next = pbase_tree;
	pbase_tree = it;

	oidcpy(&it->pcache.oid, &tree_oid);
	it->pcache.tree_data = data;
	it->pcache.tree_size = size;
}