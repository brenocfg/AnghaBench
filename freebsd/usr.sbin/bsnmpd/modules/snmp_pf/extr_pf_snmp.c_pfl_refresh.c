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
struct pfl_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct pfl_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pfl_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pfl_entry*) ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ pf_tick ; 
 int /*<<< orphan*/  pfl_table ; 
 int /*<<< orphan*/  pfl_table_age ; 
 scalar_t__ pfl_table_count ; 
 scalar_t__ pfl_walk_rulesets (char*) ; 
 scalar_t__ started ; 
 scalar_t__ this_tick ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pfl_refresh(void)
{
	struct pfl_entry *e;

	if (started && this_tick <= pf_tick)
		return (0);

	while (!TAILQ_EMPTY(&pfl_table)) {
		e = TAILQ_FIRST(&pfl_table);
		TAILQ_REMOVE(&pfl_table, e, link);
		free(e);
	}
	pfl_table_count = 0;

	if (pfl_walk_rulesets(""))
		goto err;

	pfl_table_age = time(NULL);
	pf_tick = this_tick;

	return (0);

err:
	while (!TAILQ_EMPTY(&pfl_table)) {
		e = TAILQ_FIRST(&pfl_table);
		TAILQ_REMOVE(&pfl_table, e, link);
		free(e);
	}
	pfl_table_count = 0;

	return (-1);
}