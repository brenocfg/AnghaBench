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
struct kimage {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* machine_kexec ) (struct kimage*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __ftrace_enabled_restore (int) ; 
 int __ftrace_enabled_save () ; 
 int /*<<< orphan*/  default_machine_kexec (struct kimage*) ; 
 int /*<<< orphan*/  machine_restart (int /*<<< orphan*/ *) ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  stub1 (struct kimage*) ; 
 int /*<<< orphan*/  this_cpu_disable_ftrace () ; 
 int /*<<< orphan*/  this_cpu_enable_ftrace () ; 

void machine_kexec(struct kimage *image)
{
	int save_ftrace_enabled;

	save_ftrace_enabled = __ftrace_enabled_save();
	this_cpu_disable_ftrace();

	if (ppc_md.machine_kexec)
		ppc_md.machine_kexec(image);
	else
		default_machine_kexec(image);

	this_cpu_enable_ftrace();
	__ftrace_enabled_restore(save_ftrace_enabled);

	/* Fall back to normal restart if we're still alive. */
	machine_restart(NULL);
	for(;;);
}