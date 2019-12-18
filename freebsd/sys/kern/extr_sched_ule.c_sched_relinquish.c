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
 int SWT_RELINQUISH ; 
 int SW_VOL ; 
 int /*<<< orphan*/  mi_switch (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
sched_relinquish(struct thread *td)
{
	thread_lock(td);
	mi_switch(SW_VOL | SWT_RELINQUISH, NULL);
	thread_unlock(td);
}