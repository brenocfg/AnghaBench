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
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_4__ {int /*<<< orphan*/  extent_hooks; } ;
typedef  TYPE_1__ base_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELEASE ; 
 int /*<<< orphan*/  atomic_store_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * base_extent_hooks_get (TYPE_1__*) ; 

extent_hooks_t *
base_extent_hooks_set(base_t *base, extent_hooks_t *extent_hooks) {
	extent_hooks_t *old_extent_hooks = base_extent_hooks_get(base);
	atomic_store_p(&base->extent_hooks, extent_hooks, ATOMIC_RELEASE);
	return old_extent_hooks;
}