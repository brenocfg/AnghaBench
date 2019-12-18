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
struct TYPE_2__ {int /*<<< orphan*/ ** ttys; } ;

/* Variables and functions */
 int MAX_PTYS ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 TYPE_1__ pty_slave ; 
 int /*<<< orphan*/  ttys_lock ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool devpts_pty_exists(int pty_num) {
    if (pty_num < 0 || pty_num > MAX_PTYS)
        return false;
    lock(&ttys_lock);
    bool exists = pty_slave.ttys[pty_num] != NULL;
    unlock(&ttys_lock);
    return exists;
}