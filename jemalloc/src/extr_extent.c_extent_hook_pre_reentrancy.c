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
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/ * arena_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pre_reentrancy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsd_fetch () ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 
 scalar_t__ tsdn_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsdn_tsd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
extent_hook_pre_reentrancy(tsdn_t *tsdn, arena_t *arena) {
	tsd_t *tsd = tsdn_null(tsdn) ? tsd_fetch() : tsdn_tsd(tsdn);
	if (arena == arena_get(tsd_tsdn(tsd), 0, false)) {
		/*
		 * The only legitimate case of customized extent hooks for a0 is
		 * hooks with no allocation activities.  One such example is to
		 * place metadata on pre-allocated resources such as huge pages.
		 * In that case, rely on reentrancy_level checks to catch
		 * infinite recursions.
		 */
		pre_reentrancy(tsd, NULL);
	} else {
		pre_reentrancy(tsd, arena);
	}
}