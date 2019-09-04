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
struct packed_git {int /*<<< orphan*/  pack_promisor; int /*<<< orphan*/  pack_local; struct packed_git* next; } ;
typedef  enum for_each_object_flags { ____Placeholder_for_each_object_flags } for_each_object_flags ;
typedef  int /*<<< orphan*/  each_packed_object_fn ;

/* Variables and functions */
 int FOR_EACH_OBJECT_LOCAL_ONLY ; 
 int FOR_EACH_OBJECT_PROMISOR_ONLY ; 
 int for_each_object_in_pack (struct packed_git*,int /*<<< orphan*/ ,void*,int) ; 
 struct packed_git* get_all_packs (int /*<<< orphan*/ ) ; 
 scalar_t__ open_pack_index (struct packed_git*) ; 
 int /*<<< orphan*/  prepare_packed_git (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

int for_each_packed_object(each_packed_object_fn cb, void *data,
			   enum for_each_object_flags flags)
{
	struct packed_git *p;
	int r = 0;
	int pack_errors = 0;

	prepare_packed_git(the_repository);
	for (p = get_all_packs(the_repository); p; p = p->next) {
		if ((flags & FOR_EACH_OBJECT_LOCAL_ONLY) && !p->pack_local)
			continue;
		if ((flags & FOR_EACH_OBJECT_PROMISOR_ONLY) &&
		    !p->pack_promisor)
			continue;
		if (open_pack_index(p)) {
			pack_errors = 1;
			continue;
		}
		r = for_each_object_in_pack(p, cb, data, flags);
		if (r)
			break;
	}
	return r ? r : pack_errors;
}