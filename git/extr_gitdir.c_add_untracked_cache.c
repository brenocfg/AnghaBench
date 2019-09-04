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
struct index_state {int /*<<< orphan*/  untracked; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_untracked_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ident_in_untracked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_untracked_cache (struct index_state*) ; 

void add_untracked_cache(struct index_state *istate)
{
	if (!istate->untracked) {
		new_untracked_cache(istate);
	} else {
		if (!ident_in_untracked(istate->untracked)) {
			free_untracked_cache(istate->untracked);
			new_untracked_cache(istate);
		}
	}
}