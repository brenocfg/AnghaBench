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
struct thread {scalar_t__ td_critnest; scalar_t__ td_oncpu; } ;
struct pcpu {int /*<<< orphan*/  pc_spinlocks; } ;
struct lock_object {int dummy; } ;
struct lock_instance {int dummy; } ;

/* Variables and functions */
 scalar_t__ NOCPU ; 
 struct lock_instance* find_instance (int /*<<< orphan*/ ,struct lock_object*) ; 
 struct pcpu* pcpu_find (scalar_t__) ; 
 int /*<<< orphan*/  witness_list_lock (struct lock_instance*,int (*) (char const*)) ; 

void
witness_display_spinlock(struct lock_object *lock, struct thread *owner,
    int (*prnt)(const char *fmt, ...))
{
	struct lock_instance *instance;
	struct pcpu *pc;

	if (owner->td_critnest == 0 || owner->td_oncpu == NOCPU)
		return;
	pc = pcpu_find(owner->td_oncpu);
	instance = find_instance(pc->pc_spinlocks, lock);
	if (instance != NULL)
		witness_list_lock(instance, prnt);
}