#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pid; } ;
struct TYPE_6__ {TYPE_1__ super; } ;
typedef  TYPE_2__ LinuxProcess ;
typedef  scalar_t__ IOPriority ;

/* Variables and functions */
 int /*<<< orphan*/  IOPRIO_WHO_PROCESS ; 
 scalar_t__ LinuxProcess_updateIOPriority (TYPE_2__*) ; 
 int /*<<< orphan*/  SYS_ioprio_set ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

bool LinuxProcess_setIOPriority(LinuxProcess* this, IOPriority ioprio) {
// Other OSes masquerading as Linux (NetBSD?) don't have this syscall
#ifdef SYS_ioprio_set
   syscall(SYS_ioprio_set, IOPRIO_WHO_PROCESS, this->super.pid, ioprio);
#endif
   return (LinuxProcess_updateIOPriority(this) == ioprio);
}