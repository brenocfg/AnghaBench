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
struct user_desc {unsigned int entry_number; int /*<<< orphan*/  base_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  tls_ptr; } ;
struct task {TYPE_1__ cpu; } ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int _EFAULT ; 
 scalar_t__ user_get_task (struct task*,int /*<<< orphan*/ ,struct user_desc) ; 
 scalar_t__ user_put (int /*<<< orphan*/ ,struct user_desc) ; 

int task_set_thread_area(struct task *task, addr_t u_info) {
    struct user_desc info;
    if (user_get_task(task, u_info, info))
        return _EFAULT;

    // On a real system, TLS works by creating a special segment pointing to
    // the TLS buffer. Our shitty emulation of that is to ignore attempts to
    // modify GS and add this address to any memory reference that uses GS.
    task->cpu.tls_ptr = info.base_addr;

    if (info.entry_number == (unsigned) -1) {
        info.entry_number = 0xc;
    }

    if (user_put(u_info, info))
            return _EFAULT;
    return 0;
}