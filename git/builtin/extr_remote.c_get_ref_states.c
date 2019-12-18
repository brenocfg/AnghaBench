#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct string_list_item {int /*<<< orphan*/  util; } ;
struct TYPE_8__ {int strdup_strings; } ;
struct ref_states {TYPE_3__ stale; TYPE_3__ tracked; TYPE_3__ new_refs; TYPE_2__* remote; } ;
struct ref {int /*<<< orphan*/  name; struct ref* next; TYPE_1__* peer_ref; } ;
struct TYPE_9__ {int nr; int /*<<< orphan*/ * raw; int /*<<< orphan*/ * items; } ;
struct TYPE_7__ {TYPE_5__ fetch; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abbrev_branch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_refs (struct ref*) ; 
 scalar_t__ get_fetch_map (struct ref const*,int /*<<< orphan*/ *,struct ref***,int) ; 
 struct ref* get_stale_heads (TYPE_5__*,struct ref*) ; 
 int /*<<< orphan*/  ref_exists (int /*<<< orphan*/ ) ; 
 struct string_list_item* string_list_append (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_sort (TYPE_3__*) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_ref_states(const struct ref *remote_refs, struct ref_states *states)
{
	struct ref *fetch_map = NULL, **tail = &fetch_map;
	struct ref *ref, *stale_refs;
	int i;

	for (i = 0; i < states->remote->fetch.nr; i++)
		if (get_fetch_map(remote_refs, &states->remote->fetch.items[i], &tail, 1))
			die(_("Could not get fetch map for refspec %s"),
				states->remote->fetch.raw[i]);

	states->new_refs.strdup_strings = 1;
	states->tracked.strdup_strings = 1;
	states->stale.strdup_strings = 1;
	for (ref = fetch_map; ref; ref = ref->next) {
		if (!ref->peer_ref || !ref_exists(ref->peer_ref->name))
			string_list_append(&states->new_refs, abbrev_branch(ref->name));
		else
			string_list_append(&states->tracked, abbrev_branch(ref->name));
	}
	stale_refs = get_stale_heads(&states->remote->fetch, fetch_map);
	for (ref = stale_refs; ref; ref = ref->next) {
		struct string_list_item *item =
			string_list_append(&states->stale, abbrev_branch(ref->name));
		item->util = xstrdup(ref->name);
	}
	free_refs(stale_refs);
	free_refs(fetch_map);

	string_list_sort(&states->new_refs);
	string_list_sort(&states->tracked);
	string_list_sort(&states->stale);

	return 0;
}