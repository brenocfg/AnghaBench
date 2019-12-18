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
struct shallow_info {int* ours; int* theirs; int /*<<< orphan*/  nr_theirs; int /*<<< orphan*/  nr_ours; struct oid_array* shallow; } ;
struct oid_array {int nr; int /*<<< orphan*/ * oid; } ;
struct commit_graft {scalar_t__ nr_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (int*,int) ; 
 scalar_t__ has_object_file (int /*<<< orphan*/ *) ; 
 struct commit_graft* lookup_commit_graft (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct shallow_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  trace_printf_key (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  trace_shallow ; 

void prepare_shallow_info(struct shallow_info *info, struct oid_array *sa)
{
	int i;
	trace_printf_key(&trace_shallow, "shallow: prepare_shallow_info\n");
	memset(info, 0, sizeof(*info));
	info->shallow = sa;
	if (!sa)
		return;
	ALLOC_ARRAY(info->ours, sa->nr);
	ALLOC_ARRAY(info->theirs, sa->nr);
	for (i = 0; i < sa->nr; i++) {
		if (has_object_file(sa->oid + i)) {
			struct commit_graft *graft;
			graft = lookup_commit_graft(the_repository,
						    &sa->oid[i]);
			if (graft && graft->nr_parent < 0)
				continue;
			info->ours[info->nr_ours++] = i;
		} else
			info->theirs[info->nr_theirs++] = i;
	}
}