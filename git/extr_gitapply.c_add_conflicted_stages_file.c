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
struct patch {int new_mode; int /*<<< orphan*/  new_name; int /*<<< orphan*/ * threeway_stage; } ;
struct cache_entry {int ce_namelen; int /*<<< orphan*/  oid; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  name; } ;
struct apply_state {TYPE_1__* repo; int /*<<< orphan*/  update_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CACHE_OK_TO_ADD ; 
 int S_IFREG ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ add_index_entry (int /*<<< orphan*/ ,struct cache_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ce_flags (int) ; 
 int /*<<< orphan*/  create_ce_mode (unsigned int) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 struct cache_entry* make_empty_cache_entry (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_file_from_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_conflicted_stages_file(struct apply_state *state,
				       struct patch *patch)
{
	int stage, namelen;
	unsigned mode;
	struct cache_entry *ce;

	if (!state->update_index)
		return 0;
	namelen = strlen(patch->new_name);
	mode = patch->new_mode ? patch->new_mode : (S_IFREG | 0644);

	remove_file_from_index(state->repo->index, patch->new_name);
	for (stage = 1; stage < 4; stage++) {
		if (is_null_oid(&patch->threeway_stage[stage - 1]))
			continue;
		ce = make_empty_cache_entry(state->repo->index, namelen);
		memcpy(ce->name, patch->new_name, namelen);
		ce->ce_mode = create_ce_mode(mode);
		ce->ce_flags = create_ce_flags(stage);
		ce->ce_namelen = namelen;
		oidcpy(&ce->oid, &patch->threeway_stage[stage - 1]);
		if (add_index_entry(state->repo->index, ce, ADD_CACHE_OK_TO_ADD) < 0) {
			discard_cache_entry(ce);
			return error(_("unable to add cache entry for %s"),
				     patch->new_name);
		}
	}

	return 0;
}