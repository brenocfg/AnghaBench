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
struct task {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  raise (int) ; 

__attribute__((used)) static void exit_handler(struct task *task, int code) {
    if (task->parent != NULL)
        return;
    if (code & 0xff)
        raise(code & 0xff);
    else
        exit(code >> 8);
}