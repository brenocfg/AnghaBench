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
 int /*<<< orphan*/  SY_THR_STATIC_KLD ; 
 int /*<<< orphan*/  mq32_syscalls ; 
 int /*<<< orphan*/  mq_syscalls ; 
 int syscall32_helper_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int syscall_helper_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mqinit(void)
{
	int error;

	error = syscall_helper_register(mq_syscalls, SY_THR_STATIC_KLD);
	if (error != 0)
		return (error);
#ifdef COMPAT_FREEBSD32
	error = syscall32_helper_register(mq32_syscalls, SY_THR_STATIC_KLD);
	if (error != 0)
		return (error);
#endif
	return (0);
}