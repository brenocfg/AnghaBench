#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  extent_sn_next; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 size_t atomic_fetch_add_zu (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

size_t
arena_extent_sn_next(arena_t *arena) {
	return atomic_fetch_add_zu(&arena->extent_sn_next, 1, ATOMIC_RELAXED);
}