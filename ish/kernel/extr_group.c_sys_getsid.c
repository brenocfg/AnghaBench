#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pid_t_ ;
typedef  int /*<<< orphan*/  dword_t ;
struct TYPE_4__ {TYPE_1__* group; } ;
struct TYPE_3__ {int /*<<< orphan*/  sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pids_lock ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

dword_t sys_getsid() {
    STRACE("getsid()");
    lock(&pids_lock);
    pid_t_ sid = current->group->sid;
    unlock(&pids_lock);
    return sid;
}