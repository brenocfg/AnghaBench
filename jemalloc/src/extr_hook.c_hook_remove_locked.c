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
typedef  int /*<<< orphan*/  seq_hooks_t ;
struct TYPE_4__ {int in_use; } ;
typedef  TYPE_1__ hooks_internal_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ atomic_load_u (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_u (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nhooks ; 
 int /*<<< orphan*/  seq_store_hooks (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int seq_try_load_hooks (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hook_remove_locked(seq_hooks_t *to_remove) {
	hooks_internal_t hooks_internal;
	bool success = seq_try_load_hooks(&hooks_internal, to_remove);
	/* We hold mu; no concurrent access. */
	assert(success);
	/* Should only remove hooks that were added. */
	assert(hooks_internal.in_use);
	hooks_internal.in_use = false;
	seq_store_hooks(to_remove, &hooks_internal);
	atomic_store_u(&nhooks, atomic_load_u(&nhooks, ATOMIC_RELAXED) - 1,
	    ATOMIC_RELAXED);
}