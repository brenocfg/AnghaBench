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
struct sysent {int sy_thrcnt; } ;

/* Variables and functions */
 int EINVAL ; 
 int SY_THR_STATIC ; 
 int /*<<< orphan*/  syscall_thread_drain (struct sysent*) ; 

int
kern_syscall_deregister(struct sysent *sysents, int offset,
    const struct sysent *old_sysent)
{
	struct sysent *se;

	if (offset == 0)
		return (0); /* XXX? */

	se = &sysents[offset];
	if ((se->sy_thrcnt & SY_THR_STATIC) != 0)
		return (EINVAL);
	syscall_thread_drain(se);
	sysents[offset] = *old_sysent;
	return (0);
}