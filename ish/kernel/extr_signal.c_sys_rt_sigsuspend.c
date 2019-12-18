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
typedef  int uint_t ;
typedef  scalar_t__ sigset_t_ ;
typedef  scalar_t__ int_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_4__ {long long pid; TYPE_1__* sighand; int /*<<< orphan*/  pause; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,long long) ; 
 scalar_t__ _EFAULT ; 
 scalar_t__ _EINTR ; 
 scalar_t__ _EINVAL ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigmask_set_temp_unlocked (scalar_t__) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ wait_for (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int_t sys_rt_sigsuspend(addr_t mask_addr, uint_t size) {
    if (size != sizeof(sigset_t_))
        return _EINVAL;
    sigset_t_ mask;
    if (user_get(mask_addr, mask))
        return _EFAULT;
    STRACE("sigsuspend(0x%llx) = ...\n", (long long) mask);

    lock(&current->sighand->lock);
    sigmask_set_temp_unlocked(mask);
    while (wait_for(&current->pause, &current->sighand->lock, NULL) != _EINTR)
        continue;
    unlock(&current->sighand->lock);
    STRACE("%d done sigsuspend", current->pid);
    return _EINTR;
}