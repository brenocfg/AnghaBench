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
struct ucred {int /*<<< orphan*/  cr_label; } ;
struct proc {TYPE_1__* p_ucred; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_CRED ; 
 int /*<<< orphan*/  proc_check_sched ; 

__attribute__((used)) static int
test_proc_check_sched(struct ucred *cred, struct proc *p)
{

	LABEL_CHECK(cred->cr_label, MAGIC_CRED);
	LABEL_CHECK(p->p_ucred->cr_label, MAGIC_CRED);
	COUNTER_INC(proc_check_sched);

	return (0);
}