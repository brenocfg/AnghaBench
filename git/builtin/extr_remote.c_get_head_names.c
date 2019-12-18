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
struct refspec_item {int pattern; char* src; char* dst; scalar_t__ force; } ;
struct TYPE_2__ {int strdup_strings; } ;
struct ref_states {TYPE_1__ heads; } ;
struct ref {int /*<<< orphan*/  name; struct ref* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  abbrev_branch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_ref_by_name (struct ref const*,char*) ; 
 int /*<<< orphan*/  free_refs (struct ref*) ; 
 int /*<<< orphan*/  get_fetch_map (struct ref const*,struct refspec_item*,struct ref***,int /*<<< orphan*/ ) ; 
 struct ref* guess_remote_head (int /*<<< orphan*/ ,struct ref*,int) ; 
 int /*<<< orphan*/  string_list_append (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_head_names(const struct ref *remote_refs, struct ref_states *states)
{
	struct ref *ref, *matches;
	struct ref *fetch_map = NULL, **fetch_map_tail = &fetch_map;
	struct refspec_item refspec;

	refspec.force = 0;
	refspec.pattern = 1;
	refspec.src = refspec.dst = "refs/heads/*";
	states->heads.strdup_strings = 1;
	get_fetch_map(remote_refs, &refspec, &fetch_map_tail, 0);
	matches = guess_remote_head(find_ref_by_name(remote_refs, "HEAD"),
				    fetch_map, 1);
	for (ref = matches; ref; ref = ref->next)
		string_list_append(&states->heads, abbrev_branch(ref->name));

	free_refs(fetch_map);
	free_refs(matches);

	return 0;
}