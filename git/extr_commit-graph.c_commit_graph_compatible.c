#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct repository {TYPE_3__* parsed_objects; TYPE_2__* objects; int /*<<< orphan*/  gitdir; } ;
struct TYPE_6__ {scalar_t__ grafts_nr; } ;
struct TYPE_5__ {TYPE_1__* replace_map; } ;
struct TYPE_4__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 scalar_t__ hashmap_get_size (int /*<<< orphan*/ *) ; 
 scalar_t__ is_repository_shallow (struct repository*) ; 
 int /*<<< orphan*/  prepare_commit_graft (struct repository*) ; 
 int /*<<< orphan*/  prepare_replace_object (struct repository*) ; 
 scalar_t__ read_replace_refs ; 

__attribute__((used)) static int commit_graph_compatible(struct repository *r)
{
	if (!r->gitdir)
		return 0;

	if (read_replace_refs) {
		prepare_replace_object(r);
		if (hashmap_get_size(&r->objects->replace_map->map))
			return 0;
	}

	prepare_commit_graft(r);
	if (r->parsed_objects && r->parsed_objects->grafts_nr)
		return 0;
	if (is_repository_shallow(r))
		return 0;

	return 1;
}