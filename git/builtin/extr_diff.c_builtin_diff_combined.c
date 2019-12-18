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
struct rev_info {int dense_combined_merges; int combine_merges; } ;
struct oid_array {int dummy; } ;
struct object_array_entry {TYPE_1__* item; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 struct oid_array OID_ARRAY_INIT ; 
 int /*<<< orphan*/  builtin_diff_usage ; 
 int /*<<< orphan*/  diff_tree_combined (int /*<<< orphan*/ *,struct oid_array*,int,struct rev_info*) ; 
 int /*<<< orphan*/  oid_array_append (struct oid_array*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_array_clear (struct oid_array*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int builtin_diff_combined(struct rev_info *revs,
				 int argc, const char **argv,
				 struct object_array_entry *ent,
				 int ents)
{
	struct oid_array parents = OID_ARRAY_INIT;
	int i;

	if (argc > 1)
		usage(builtin_diff_usage);

	if (!revs->dense_combined_merges && !revs->combine_merges)
		revs->dense_combined_merges = revs->combine_merges = 1;
	for (i = 1; i < ents; i++)
		oid_array_append(&parents, &ent[i].item->oid);
	diff_tree_combined(&ent[0].item->oid, &parents,
			   revs->dense_combined_merges, revs);
	oid_array_clear(&parents);
	return 0;
}