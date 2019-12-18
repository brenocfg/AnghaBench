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
typedef  int /*<<< orphan*/  u64 ;
struct spin_multi_state {int loops; int /*<<< orphan*/  exit_wait; int /*<<< orphan*/  enter_wait; int /*<<< orphan*/  start_wait; int /*<<< orphan*/  lock; } ;
struct spin_multi_per_thread {int /*<<< orphan*/  start; struct spin_multi_state* state; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  __RAW_SPIN_LOCK_UNLOCKED (char*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/  (*) (struct spin_multi_per_thread*),struct spin_multi_per_thread*,char*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multi_other (struct spin_multi_per_thread*) ; 

__attribute__((used)) static int multi_get(void *data, u64 *val)
{
	ktime_t finish;
	struct spin_multi_state ms;
	struct spin_multi_per_thread t1, t2;

	ms.lock = __RAW_SPIN_LOCK_UNLOCKED("multi_get");
	ms.loops = 1000000;

	atomic_set(&ms.start_wait, 2);
	atomic_set(&ms.enter_wait, 2);
	atomic_set(&ms.exit_wait, 2);
	t1.state = &ms;
	t2.state = &ms;

	kthread_run(multi_other, &t2, "multi_get");

	multi_other(&t1);

	finish = ktime_get();

	*val = ktime_us_delta(finish, t1.start);

	return 0;
}