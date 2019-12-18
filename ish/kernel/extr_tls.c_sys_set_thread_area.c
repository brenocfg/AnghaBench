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
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int task_set_thread_area (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sys_set_thread_area(addr_t u_info) {
    STRACE("set_thread_area(0x%x)", u_info);
    return task_set_thread_area(current, u_info);
}