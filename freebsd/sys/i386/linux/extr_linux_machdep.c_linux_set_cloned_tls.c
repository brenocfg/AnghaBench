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
struct thread {TYPE_1__* td_pcb; } ;
struct segment_descriptor {int dummy; } ;
struct l_user_desc {int entry_number; } ;
typedef  int /*<<< orphan*/  a ;
struct TYPE_2__ {int /*<<< orphan*/  pcb_gs; struct segment_descriptor pcb_gsd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUGS_SEL ; 
 int LINUX_LDT_entry_a (struct l_user_desc*) ; 
 int LINUX_LDT_entry_b (struct l_user_desc*) ; 
 int /*<<< orphan*/  SEL_UPL ; 
 int copyin (void*,struct l_user_desc*,int) ; 
 int copyout (struct l_user_desc*,void*,int) ; 
 int /*<<< orphan*/  linux_msg (struct thread*,char*) ; 
 int /*<<< orphan*/  memcpy (struct segment_descriptor*,int**,int) ; 

int
linux_set_cloned_tls(struct thread *td, void *desc)
{
	struct segment_descriptor sd;
	struct l_user_desc info;
	int idx, error;
	int a[2];

	error = copyin(desc, &info, sizeof(struct l_user_desc));
	if (error) {
		linux_msg(td, "set_cloned_tls copyin failed!");
	} else {
		idx = info.entry_number;

		/*
		 * looks like we're getting the idx we returned
		 * in the set_thread_area() syscall
		 */
		if (idx != 6 && idx != 3) {
			linux_msg(td, "set_cloned_tls resetting idx!");
			idx = 3;
		}

		/* this doesnt happen in practice */
		if (idx == 6) {
			/* we might copy out the entry_number as 3 */
			info.entry_number = 3;
			error = copyout(&info, desc, sizeof(struct l_user_desc));
			if (error)
				linux_msg(td, "set_cloned_tls copyout failed!");
		}

		a[0] = LINUX_LDT_entry_a(&info);
		a[1] = LINUX_LDT_entry_b(&info);

		memcpy(&sd, &a, sizeof(a));
		/* set %gs */
		td->td_pcb->pcb_gsd = sd;
		td->td_pcb->pcb_gs = GSEL(GUGS_SEL, SEL_UPL);
	}

	return (error);
}