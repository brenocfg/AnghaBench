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
struct index_state {struct cache_entry** cache; } ;
struct checkout {int dummy; } ;
struct cache_entry {int ce_flags; } ;

/* Variables and functions */
 int CE_UPDATE ; 
 int CE_WT_REMOVE ; 
 int /*<<< orphan*/  GITMODULES_FILE ; 
 int /*<<< orphan*/  checkout_entry (struct cache_entry*,struct checkout*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int index_name_pos (struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_read_gitmodules (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submodule_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void load_gitmodules_file(struct index_state *index,
				 struct checkout *state)
{
	int pos = index_name_pos(index, GITMODULES_FILE, strlen(GITMODULES_FILE));

	if (pos >= 0) {
		struct cache_entry *ce = index->cache[pos];
		if (!state && ce->ce_flags & CE_WT_REMOVE) {
			repo_read_gitmodules(the_repository);
		} else if (state && (ce->ce_flags & CE_UPDATE)) {
			submodule_free(the_repository);
			checkout_entry(ce, state, NULL, NULL);
			repo_read_gitmodules(the_repository);
		}
	}
}