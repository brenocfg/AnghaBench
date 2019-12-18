#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcpu {int /*<<< orphan*/  pc_mid; } ;
struct intr_vector {TYPE_1__* iv_ic; int /*<<< orphan*/  iv_mid; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ic_assign ) (struct intr_vector*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int NOCPU ; 
 scalar_t__ assign_cpu ; 
 int /*<<< orphan*/  intr_table_lock ; 
 struct pcpu* pcpu_find (int) ; 
 int /*<<< orphan*/  stub1 (struct intr_vector*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
intr_assign_cpu(void *arg, int cpu)
{
#ifdef SMP
	struct pcpu *pc;
	struct intr_vector *iv;

	/*
	 * Don't do anything during early boot.  We will pick up the
	 * assignment once the APs are started.
	 */
	if (assign_cpu && cpu != NOCPU) {
		pc = pcpu_find(cpu);
		if (pc == NULL)
			return (EINVAL);
		iv = arg;
		sx_xlock(&intr_table_lock);
		iv->iv_mid = pc->pc_mid;
		iv->iv_ic->ic_assign(iv);
		sx_xunlock(&intr_table_lock);
	}
	return (0);
#else
	return (EOPNOTSUPP);
#endif
}