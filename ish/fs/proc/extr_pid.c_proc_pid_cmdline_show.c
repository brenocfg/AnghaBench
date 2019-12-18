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
typedef  int /*<<< orphan*/  uint8_t ;
struct task {TYPE_1__* mm; } ;
struct proc_entry {int dummy; } ;
struct proc_data {int dummy; } ;
struct TYPE_2__ {size_t argv_end; size_t argv_start; } ;

/* Variables and functions */
 int _ENOMEM ; 
 int _ESRCH ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  proc_buf_write (struct proc_data*,int /*<<< orphan*/ *,size_t) ; 
 struct task* proc_get_task (struct proc_entry*) ; 
 int /*<<< orphan*/  proc_put_task (struct task*) ; 
 int user_read_task (struct task*,size_t,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int proc_pid_cmdline_show(struct proc_entry *entry, struct proc_data *buf) {
    struct task *task = proc_get_task(entry);
    if (task == NULL)
        return _ESRCH;
    size_t size = task->mm->argv_end - task->mm->argv_start;
    uint8_t *data = malloc(size);
    if (data == NULL)
        return _ENOMEM;
    int fail = user_read_task(task, task->mm->argv_start, data, size);
    proc_buf_write(buf, data, size);
    free(data);
    proc_put_task(task);
    if (fail)
        return 0;
    return size;
}