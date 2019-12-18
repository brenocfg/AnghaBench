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
struct vfork_info {int done; int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ eax; } ;
struct task {int pid; struct vfork_info* vfork; TYPE_1__ cpu; } ;
typedef  int pid_t ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int CLONE_SIGHAND_ ; 
 int CLONE_THREAD_ ; 
 int CLONE_VFORK_ ; 
 int CLONE_VM_ ; 
 int CSIGNAL_ ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int IMPLEMENTED_FLAGS ; 
 int /*<<< orphan*/  STRACE (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _EINVAL ; 
 int _ENOMEM ; 
 int /*<<< orphan*/  cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_init (int /*<<< orphan*/ *) ; 
 int copy_task (struct task*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_init (int /*<<< orphan*/ *) ; 
 struct task* task_create_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_destroy (struct task*) ; 
 int /*<<< orphan*/  task_start (struct task*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_ignore_signals (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

dword_t sys_clone(dword_t flags, addr_t stack, addr_t ptid, addr_t tls, addr_t ctid) {
    STRACE("clone(0x%x, 0x%x, 0x%x, 0x%x, 0x%x)", flags, stack, ptid, tls, ctid);
    if (flags & ~CSIGNAL_ & ~IMPLEMENTED_FLAGS) {
        FIXME("unimplemented clone flags 0x%x", flags & ~CSIGNAL_ & ~IMPLEMENTED_FLAGS);
        return _EINVAL;
    }
    if (flags & CLONE_SIGHAND_ && !(flags & CLONE_VM_))
        return _EINVAL;
    if (flags & CLONE_THREAD_ && !(flags & CLONE_SIGHAND_))
        return _EINVAL;

    struct task *task = task_create_(current);
    if (task == NULL)
        return _ENOMEM;
    int err = copy_task(task, flags, stack, ptid, tls, ctid);
    if (err < 0) {
        task_destroy(task);
        return err;
    }
    task->cpu.eax = 0;

    struct vfork_info vfork;
    if (flags & CLONE_VFORK_) {
        lock_init(&vfork.lock);
        cond_init(&vfork.cond);
        vfork.done = false;
        task->vfork = &vfork;
    }

    // task might be destroyed by the time we finish, so save the pid
    pid_t pid = task->pid;
    task_start(task);

    if (flags & CLONE_VFORK_) {
        lock(&vfork.lock);
        while (!vfork.done)
            // FIXME this should stop waiting if a fatal signal is received
            wait_for_ignore_signals(&vfork.cond, &vfork.lock, NULL);
        unlock(&vfork.lock);
        task->vfork = NULL;
        cond_destroy(&vfork.cond);
    }
    return pid;
}