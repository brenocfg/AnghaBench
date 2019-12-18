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
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  freebsd32_sysent ; 
 int kern_syscall_module_handler (int /*<<< orphan*/ ,struct module*,int,void*) ; 

int
syscall32_module_handler(struct module *mod, int what, void *arg)
{

	return (kern_syscall_module_handler(freebsd32_sysent, mod, what, arg));
}