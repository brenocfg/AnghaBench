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
 int kern_syscall_helper_unregister (int /*<<< orphan*/ ,struct syscall_helper_data*) ; 
 int /*<<< orphan*/  sysent ; 

int
syscall_helper_unregister(struct syscall_helper_data *sd)
{

	return (kern_syscall_helper_unregister(sysent, sd));
}