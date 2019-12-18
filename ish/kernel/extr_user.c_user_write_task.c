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
struct task {int /*<<< orphan*/  mem; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_WRITE ; 
 char* mem_ptr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

int user_write_task(struct task *task, addr_t addr, const void *buf, size_t count) {
    const char *cbuf = (const char *) buf;
    size_t i = 0;
    while (i < count) {
        char *ptr = mem_ptr(task->mem, addr + i, MEM_WRITE);
        if (ptr == NULL)
            return 1;
        *ptr = cbuf[i++];
    }
    return 0;
}