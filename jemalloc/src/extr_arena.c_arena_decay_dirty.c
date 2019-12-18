#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_4__ {int /*<<< orphan*/  eset_dirty; int /*<<< orphan*/  decay_dirty; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int arena_decay_impl (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static bool
arena_decay_dirty(tsdn_t *tsdn, arena_t *arena, bool is_background_thread,
    bool all) {
	return arena_decay_impl(tsdn, arena, &arena->decay_dirty,
	    &arena->eset_dirty, is_background_thread, all);
}