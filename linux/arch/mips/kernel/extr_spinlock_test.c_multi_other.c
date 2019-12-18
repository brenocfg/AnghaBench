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
struct spin_multi_state {int loops; int /*<<< orphan*/  exit_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  start_wait; int /*<<< orphan*/  enter_wait; } ;
struct spin_multi_per_thread {int /*<<< orphan*/  start; struct spin_multi_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int multi_other(void *data)
{
	int loops;
	int cont;
	struct spin_multi_per_thread *pt = data;
	struct spin_multi_state *s = pt->state;

	loops = s->loops;
	cont = 1;

	atomic_dec(&s->enter_wait);

	while (atomic_read(&s->enter_wait))
		; /* spin */

	pt->start = ktime_get();

	atomic_dec(&s->start_wait);

	while (atomic_read(&s->start_wait))
		; /* spin */

	while (cont) {
		raw_spin_lock(&s->lock);
		loops--;
		if (loops == 0)
			cont = 0;
		raw_spin_unlock(&s->lock);
	}

	atomic_dec(&s->exit_wait);
	while (atomic_read(&s->exit_wait))
		; /* spin */
	return 0;
}