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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  ctl_arena_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/ * arenas_i (unsigned int) ; 
 int /*<<< orphan*/  ctl_arena_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_arena_stats_amerge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_arena_stats_sdmerge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ctl_arena_refresh(tsdn_t *tsdn, arena_t *arena, ctl_arena_t *ctl_sdarena,
    unsigned i, bool destroyed) {
	ctl_arena_t *ctl_arena = arenas_i(i);

	ctl_arena_clear(ctl_arena);
	ctl_arena_stats_amerge(tsdn, ctl_arena, arena);
	/* Merge into sum stats as well. */
	ctl_arena_stats_sdmerge(ctl_sdarena, ctl_arena, destroyed);
}