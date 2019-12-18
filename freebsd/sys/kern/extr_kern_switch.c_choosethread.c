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
 int /*<<< orphan*/  TD_SET_RUNNING (struct thread*) ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 struct thread* choosethread_panic (struct thread*) ; 
 int /*<<< orphan*/ * panicstr ; 
 struct thread* sched_choose () ; 

struct thread *
choosethread(void)
{
	struct thread *td;

	td = sched_choose();

	if (__predict_false(panicstr != NULL))
		return (choosethread_panic(td));

	TD_SET_RUNNING(td);
	return (td);
}