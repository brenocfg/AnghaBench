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
struct thread {int dummy; } ;
struct reboot_args {int /*<<< orphan*/  opt; } ;
struct linux_reboot_args {scalar_t__ magic1; int magic2; int cmd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PRIV_REBOOT ; 
 int /*<<< orphan*/  RB_HALT ; 
 int /*<<< orphan*/  RB_POWEROFF ; 
#define  REBOOT_CAD_OFF 136 
#define  REBOOT_CAD_ON 135 
#define  REBOOT_HALT 134 
 scalar_t__ REBOOT_MAGIC1 ; 
#define  REBOOT_MAGIC2 133 
#define  REBOOT_MAGIC2A 132 
#define  REBOOT_MAGIC2B 131 
#define  REBOOT_POWEROFF 130 
#define  REBOOT_RESTART 129 
#define  REBOOT_RESTART2 128 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int sys_reboot (struct thread*,struct reboot_args*) ; 

int
linux_reboot(struct thread *td, struct linux_reboot_args *args)
{
	struct reboot_args bsd_args;

	if (args->magic1 != REBOOT_MAGIC1)
		return (EINVAL);

	switch (args->magic2) {
	case REBOOT_MAGIC2:
	case REBOOT_MAGIC2A:
	case REBOOT_MAGIC2B:
		break;
	default:
		return (EINVAL);
	}

	switch (args->cmd) {
	case REBOOT_CAD_ON:
	case REBOOT_CAD_OFF:
		return (priv_check(td, PRIV_REBOOT));
	case REBOOT_HALT:
		bsd_args.opt = RB_HALT;
		break;
	case REBOOT_RESTART:
	case REBOOT_RESTART2:
		bsd_args.opt = 0;
		break;
	case REBOOT_POWEROFF:
		bsd_args.opt = RB_POWEROFF;
		break;
	default:
		return (EINVAL);
	}
	return (sys_reboot(td, &bsd_args));
}