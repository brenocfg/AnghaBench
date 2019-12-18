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
typedef  int /*<<< orphan*/  sy_call_t ;
struct sysent {scalar_t__ sy_thrcnt; int /*<<< orphan*/ * sy_call; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENFILE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NO_SYSCALL ; 
 int SYS_MAXSYSCALL ; 
 scalar_t__ SY_THR_ABSENT ; 
 int SY_THR_STATIC ; 
 int /*<<< orphan*/  atomic_store_rel_32 (scalar_t__*,int) ; 
 scalar_t__ lkmnosys ; 
 scalar_t__ lkmressys ; 

int
kern_syscall_register(struct sysent *sysents, int *offset,
    struct sysent *new_sysent, struct sysent *old_sysent, int flags)
{
	int i;

	if ((flags & ~SY_THR_STATIC) != 0)
		return (EINVAL);

	if (*offset == NO_SYSCALL) {
		for (i = 1; i < SYS_MAXSYSCALL; ++i)
			if (sysents[i].sy_call == (sy_call_t *)lkmnosys)
				break;
		if (i == SYS_MAXSYSCALL)
			return (ENFILE);
		*offset = i;
	} else if (*offset < 0 || *offset >= SYS_MAXSYSCALL)
		return (EINVAL);
	else if (sysents[*offset].sy_call != (sy_call_t *)lkmnosys &&
	    sysents[*offset].sy_call != (sy_call_t *)lkmressys)
		return (EEXIST);

	KASSERT(sysents[*offset].sy_thrcnt == SY_THR_ABSENT,
	    ("dynamic syscall is not protected"));
	*old_sysent = sysents[*offset];
	new_sysent->sy_thrcnt = SY_THR_ABSENT;
	sysents[*offset] = *new_sysent;
	atomic_store_rel_32(&sysents[*offset].sy_thrcnt, flags);
	return (0);
}