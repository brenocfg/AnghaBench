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
typedef  int /*<<< orphan*/  sy_call_t ;
struct TYPE_4__ {int /*<<< orphan*/ * sy_call; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sy_call; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_PRI_LAST ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t FREEBSD32_SYS_chdir ; 
 size_t FREEBSD32_SYS_link ; 
 size_t FREEBSD32_SYS_linkat ; 
 size_t FREEBSD32_SYS_open ; 
 size_t FREEBSD32_SYS_openat ; 
 size_t FREEBSD32_SYS_rename ; 
 size_t FREEBSD32_SYS_symlink ; 
 size_t FREEBSD32_SYS_unlink ; 
 size_t SYS_chdir ; 
 size_t SYS_link ; 
 size_t SYS_linkat ; 
 size_t SYS_open ; 
 size_t SYS_openat ; 
 size_t SYS_rename ; 
 size_t SYS_symlink ; 
 size_t SYS_unlink ; 
 int /*<<< orphan*/  filemon_event_process_exec ; 
 int /*<<< orphan*/  filemon_event_process_exit ; 
 int /*<<< orphan*/  filemon_event_process_fork ; 
 void* filemon_exec_tag ; 
 void* filemon_exit_tag ; 
 void* filemon_fork_tag ; 
 scalar_t__ filemon_wrapper_chdir ; 
 scalar_t__ filemon_wrapper_link ; 
 scalar_t__ filemon_wrapper_linkat ; 
 scalar_t__ filemon_wrapper_open ; 
 scalar_t__ filemon_wrapper_openat ; 
 scalar_t__ filemon_wrapper_rename ; 
 scalar_t__ filemon_wrapper_symlink ; 
 scalar_t__ filemon_wrapper_unlink ; 
 TYPE_2__* freebsd32_sysent ; 
 int /*<<< orphan*/  process_exec ; 
 int /*<<< orphan*/  process_exit ; 
 int /*<<< orphan*/  process_fork ; 
 TYPE_1__* sysent ; 

__attribute__((used)) static void
filemon_wrapper_install(void)
{

	sysent[SYS_chdir].sy_call = (sy_call_t *) filemon_wrapper_chdir;
	sysent[SYS_open].sy_call = (sy_call_t *) filemon_wrapper_open;
	sysent[SYS_openat].sy_call = (sy_call_t *) filemon_wrapper_openat;
	sysent[SYS_rename].sy_call = (sy_call_t *) filemon_wrapper_rename;
	sysent[SYS_unlink].sy_call = (sy_call_t *) filemon_wrapper_unlink;
	sysent[SYS_link].sy_call = (sy_call_t *) filemon_wrapper_link;
	sysent[SYS_symlink].sy_call = (sy_call_t *) filemon_wrapper_symlink;
	sysent[SYS_linkat].sy_call = (sy_call_t *) filemon_wrapper_linkat;

#if defined(COMPAT_FREEBSD32)
	freebsd32_sysent[FREEBSD32_SYS_chdir].sy_call = (sy_call_t *) filemon_wrapper_chdir;
	freebsd32_sysent[FREEBSD32_SYS_open].sy_call = (sy_call_t *) filemon_wrapper_open;
	freebsd32_sysent[FREEBSD32_SYS_openat].sy_call = (sy_call_t *) filemon_wrapper_openat;
	freebsd32_sysent[FREEBSD32_SYS_rename].sy_call = (sy_call_t *) filemon_wrapper_rename;
	freebsd32_sysent[FREEBSD32_SYS_unlink].sy_call = (sy_call_t *) filemon_wrapper_unlink;
	freebsd32_sysent[FREEBSD32_SYS_link].sy_call = (sy_call_t *) filemon_wrapper_link;
	freebsd32_sysent[FREEBSD32_SYS_symlink].sy_call = (sy_call_t *) filemon_wrapper_symlink;
	freebsd32_sysent[FREEBSD32_SYS_linkat].sy_call = (sy_call_t *) filemon_wrapper_linkat;
#endif	/* COMPAT_FREEBSD32 */

	filemon_exec_tag = EVENTHANDLER_REGISTER(process_exec,
	    filemon_event_process_exec, NULL, EVENTHANDLER_PRI_LAST);
	filemon_exit_tag = EVENTHANDLER_REGISTER(process_exit,
	    filemon_event_process_exit, NULL, EVENTHANDLER_PRI_LAST);
	filemon_fork_tag = EVENTHANDLER_REGISTER(process_fork,
	    filemon_event_process_fork, NULL, EVENTHANDLER_PRI_LAST);
}