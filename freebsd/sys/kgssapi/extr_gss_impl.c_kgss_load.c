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
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SY_THR_STATIC_KLD ; 
 int /*<<< orphan*/  gssd_syscalls ; 
 int /*<<< orphan*/  kgss_mechs ; 
 int syscall_helper_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kgss_load(void)
{
	int error;

	LIST_INIT(&kgss_mechs);
	error = syscall_helper_register(gssd_syscalls, SY_THR_STATIC_KLD);
	if (error != 0)
		return (error);
	return (0);
}