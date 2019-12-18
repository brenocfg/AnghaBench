#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ current_pid; int /*<<< orphan*/  lpp; } ;
struct TYPE_3__ {scalar_t__ pid; } ;

/* Variables and functions */
 TYPE_2__ S390_lowcore ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  lpp (int /*<<< orphan*/ *) ; 
 scalar_t__ test_facility (int) ; 

void arch_setup_new_exec(void)
{
	if (S390_lowcore.current_pid != current->pid) {
		S390_lowcore.current_pid = current->pid;
		if (test_facility(40))
			lpp(&S390_lowcore.lpp);
	}
}