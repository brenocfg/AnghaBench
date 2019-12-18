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
struct TYPE_3__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  cnts; } ;
typedef  TYPE_1__ arch_rwlock_t ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __atomic_add_const (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void arch_read_lock_wait(arch_rwlock_t *rw)
{
	if (unlikely(in_interrupt())) {
		while (READ_ONCE(rw->cnts) & 0x10000)
			barrier();
		return;
	}

	/* Remove this reader again to allow recursive read locking */
	__atomic_add_const(-1, &rw->cnts);
	/* Put the reader into the wait queue */
	arch_spin_lock(&rw->wait);
	/* Now add this reader to the count value again */
	__atomic_add_const(1, &rw->cnts);
	/* Loop until the writer is done */
	while (READ_ONCE(rw->cnts) & 0x10000)
		barrier();
	arch_spin_unlock(&rw->wait);
}