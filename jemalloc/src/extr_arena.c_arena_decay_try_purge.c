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
typedef  int /*<<< orphan*/  eset_t ;
typedef  int /*<<< orphan*/  arena_t ;
typedef  int /*<<< orphan*/  arena_decay_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_decay_to_limit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,size_t,size_t,int) ; 

__attribute__((used)) static void
arena_decay_try_purge(tsdn_t *tsdn, arena_t *arena, arena_decay_t *decay,
    eset_t *eset, size_t current_npages, size_t npages_limit,
    bool is_background_thread) {
	if (current_npages > npages_limit) {
		arena_decay_to_limit(tsdn, arena, decay, eset, false,
		    npages_limit, current_npages - npages_limit,
		    is_background_thread);
	}
}