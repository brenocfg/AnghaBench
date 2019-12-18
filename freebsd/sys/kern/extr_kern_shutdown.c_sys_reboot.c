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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct reboot_args {int opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIV_REBOOT ; 
 int RB_REROOT ; 
 int /*<<< orphan*/  kern_reboot (int) ; 
 int kern_reroot () ; 
 int mac_system_check_reboot (int /*<<< orphan*/ ,int) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 

int
sys_reboot(struct thread *td, struct reboot_args *uap)
{
	int error;

	error = 0;
#ifdef MAC
	error = mac_system_check_reboot(td->td_ucred, uap->opt);
#endif
	if (error == 0)
		error = priv_check(td, PRIV_REBOOT);
	if (error == 0) {
		if (uap->opt & RB_REROOT)
			error = kern_reroot();
		else
			kern_reboot(uap->opt);
	}
	return (error);
}