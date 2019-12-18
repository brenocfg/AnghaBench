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
struct sysent {int dummy; } ;
struct syscall_helper_data {scalar_t__ registered; int /*<<< orphan*/  old_sysent; int /*<<< orphan*/  syscall_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  kern_syscall_deregister (struct sysent*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
kern_syscall_helper_unregister(struct sysent *sysents,
    struct syscall_helper_data *sd)
{
	struct syscall_helper_data *sd1;

	for (sd1 = sd; sd1->registered != 0; sd1++) {
		kern_syscall_deregister(sysents, sd1->syscall_no,
		    &sd1->old_sysent);
		sd1->registered = 0;
	}
	return (0);
}