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
struct timespec {int dummy; } ;
struct futex {int /*<<< orphan*/  cond; } ;
typedef  scalar_t__ dword_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ) ; 
 int _EAGAIN ; 
 int _EFAULT ; 
 TYPE_1__* current ; 
 struct futex* futex_get (int /*<<< orphan*/ ) ; 
 scalar_t__ futex_load (struct futex*,scalar_t__*) ; 
 int /*<<< orphan*/  futex_lock ; 
 int /*<<< orphan*/  futex_put (struct futex*) ; 
 int wait_for (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 

int futex_wait(addr_t uaddr, dword_t val, struct timespec *timeout) {
    struct futex *futex = futex_get(uaddr);
    int err = 0;
    dword_t tmp;
    if (futex_load(futex, &tmp))
        err = _EFAULT;
    else if (tmp != val)
        err = _EAGAIN;
    else
        err = wait_for(&futex->cond, &futex_lock, timeout);
    futex_put(futex);
    STRACE("%d end futex(FUTEX_WAIT)", current->pid);
    return err;
}