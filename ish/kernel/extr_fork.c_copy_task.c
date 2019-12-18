#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct tgroup {int /*<<< orphan*/  lock; int /*<<< orphan*/  threads; struct task* leader; } ;
struct TYPE_13__ {scalar_t__ esp; } ;
struct task {int exit_signal; struct mm* mm; TYPE_8__* files; TYPE_5__* fs; TYPE_2__* sighand; scalar_t__ clear_tid; int /*<<< orphan*/  pid; int /*<<< orphan*/  group_links; struct tgroup* group; int /*<<< orphan*/  tgid; TYPE_1__ cpu; int /*<<< orphan*/ * vfork; } ;
struct mm {int dummy; } ;
typedef  int dword_t ;
typedef  scalar_t__ addr_t ;
struct TYPE_16__ {int /*<<< orphan*/  refcount; } ;
struct TYPE_15__ {int /*<<< orphan*/  refcount; } ;
struct TYPE_14__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int CLONE_CHILD_CLEARTID_ ; 
 int CLONE_CHILD_SETTID_ ; 
 int CLONE_FILES_ ; 
 int CLONE_FS_ ; 
 int CLONE_PARENT_SETTID_ ; 
 int CLONE_SETTLS_ ; 
 int CLONE_SIGHAND_ ; 
 int CLONE_THREAD_ ; 
 int CLONE_VM_ ; 
 int CSIGNAL_ ; 
 scalar_t__ IS_ERR (TYPE_8__*) ; 
 int PTR_ERR (TYPE_8__*) ; 
 int _EFAULT ; 
 int _ENOMEM ; 
 TYPE_8__* fdtable_copy (TYPE_8__*) ; 
 int /*<<< orphan*/  fdtable_release (TYPE_8__*) ; 
 TYPE_5__* fs_info_copy (TYPE_5__*) ; 
 int /*<<< orphan*/  fs_info_release (TYPE_5__*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_copy (struct mm*) ; 
 int /*<<< orphan*/  mm_release (struct mm*) ; 
 int /*<<< orphan*/  mm_retain (struct mm*) ; 
 int /*<<< orphan*/  pids_lock ; 
 TYPE_2__* sighand_copy (TYPE_2__*) ; 
 int /*<<< orphan*/  sighand_release (TYPE_2__*) ; 
 int /*<<< orphan*/  task_set_mm (struct task*,int /*<<< orphan*/ ) ; 
 int task_set_thread_area (struct task*,scalar_t__) ; 
 struct tgroup* tgroup_copy (struct tgroup*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_put (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ user_put_task (struct task*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int copy_task(struct task *task, dword_t flags, addr_t stack, addr_t ptid_addr, addr_t tls_addr, addr_t ctid_addr) {
    task->vfork = NULL;
    if (stack != 0)
        task->cpu.esp = stack;

    int err;
    struct mm *mm = task->mm;
    if (flags & CLONE_VM_) {
        mm_retain(mm);
    } else {
        task_set_mm(task, mm_copy(mm));
    }

    if (flags & CLONE_FILES_) {
        task->files->refcount++;
    } else {
        task->files = fdtable_copy(task->files);
        if (IS_ERR(task->files)) {
            err = PTR_ERR(task->files);
            goto fail_free_mem;
        }
    }

    err = _ENOMEM;
    if (flags & CLONE_FS_) {
        task->fs->refcount++;
    } else {
        task->fs = fs_info_copy(task->fs);
        if (task->fs == NULL)
            goto fail_free_files;
    }

    if (flags & CLONE_SIGHAND_) {
        task->sighand->refcount++;
    } else {
        task->sighand = sighand_copy(task->sighand);
        if (task->sighand == NULL)
            goto fail_free_fs;
    }

    struct tgroup *old_group = task->group;
    lock(&pids_lock);
    lock(&old_group->lock);
    if (!(flags & CLONE_THREAD_)) {
        task->group = tgroup_copy(old_group);
        task->group->leader = task;
        task->tgid = task->pid;
    }
    list_add(&task->group->threads, &task->group_links);
    unlock(&old_group->lock);
    unlock(&pids_lock);

    if (flags & CLONE_SETTLS_) {
        err = task_set_thread_area(task, tls_addr);
        if (err < 0)
            goto fail_free_sighand;
    }

    err = _EFAULT;
    if (flags & CLONE_CHILD_SETTID_)
        if (user_put_task(task, ctid_addr, task->pid))
            goto fail_free_sighand;
    if (flags & CLONE_PARENT_SETTID_)
        if (user_put(ptid_addr, task->pid))
            goto fail_free_sighand;
    if (flags & CLONE_CHILD_CLEARTID_)
        task->clear_tid = ctid_addr;
    task->exit_signal = flags & CSIGNAL_;

    // remember to do CLONE_SYSVSEM
    return 0;

fail_free_sighand:
    sighand_release(task->sighand);
fail_free_fs:
    fs_info_release(task->fs);
fail_free_files:
    fdtable_release(task->files);
fail_free_mem:
    mm_release(task->mm);
    return err;
}