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
struct task {TYPE_1__* files; } ;
struct proc_entry {int /*<<< orphan*/  fd; } ;
struct fd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int _ESRCH ; 
 struct fd* fdtable_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int generic_getpath (struct fd*,char*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 struct task* proc_get_task (struct proc_entry*) ; 
 int /*<<< orphan*/  proc_put_task (struct task*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int proc_pid_fd_readlink(struct proc_entry *entry, char *buf) {
    struct task *task = proc_get_task(entry);
    if (task == NULL)
        return _ESRCH;
    lock(&task->files->lock);
    struct fd *fd = fdtable_get(task->files, entry->fd);
    int err = generic_getpath(fd, buf);
    unlock(&task->files->lock);
    proc_put_task(task);
    return err;
}