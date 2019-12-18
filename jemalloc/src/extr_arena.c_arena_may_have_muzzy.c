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
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 scalar_t__ arena_muzzy_decay_ms_get (int /*<<< orphan*/ *) ; 
 scalar_t__ pages_can_purge_lazy ; 

__attribute__((used)) static bool
arena_may_have_muzzy(arena_t *arena) {
	return (pages_can_purge_lazy && (arena_muzzy_decay_ms_get(arena) != 0));
}