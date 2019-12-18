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
struct task {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task*) ; 
 int PTR_ERR (struct task*) ; 
 struct task* construct_task (int /*<<< orphan*/ *) ; 
 struct task* current ; 
 int /*<<< orphan*/  establish_signal_handlers () ; 

int become_first_process() {
    // now seems like a nice time
    establish_signal_handlers();

    struct task *task = construct_task(NULL);
    if (IS_ERR(task))
        return PTR_ERR(task);

    current = task;
    return 0;
}