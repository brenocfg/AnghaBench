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
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  td_slpq ; 
 int /*<<< orphan*/  zombie_lock ; 
 int /*<<< orphan*/  zombie_threads ; 

void
thread_zombie(struct thread *td)
{
	mtx_lock_spin(&zombie_lock);
	TAILQ_INSERT_HEAD(&zombie_threads, td, td_slpq);
	mtx_unlock_spin(&zombie_lock);
}