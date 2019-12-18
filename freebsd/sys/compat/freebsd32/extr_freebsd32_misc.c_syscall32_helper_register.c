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
struct syscall_helper_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  freebsd32_sysent ; 
 int kern_syscall_helper_register (int /*<<< orphan*/ ,struct syscall_helper_data*,int) ; 

int
syscall32_helper_register(struct syscall_helper_data *sd, int flags)
{

	return (kern_syscall_helper_register(freebsd32_sysent, sd, flags));
}