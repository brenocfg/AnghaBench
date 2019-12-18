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

/* Variables and functions */
 int /*<<< orphan*/  mq32_syscalls ; 
 int /*<<< orphan*/  mq_syscalls ; 
 int /*<<< orphan*/  syscall32_helper_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscall_helper_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mqunload(void)
{

#ifdef COMPAT_FREEBSD32
	syscall32_helper_unregister(mq32_syscalls);
#endif
	syscall_helper_unregister(mq_syscalls);
	return (0);
}