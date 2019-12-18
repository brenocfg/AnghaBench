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
struct thread {TYPE_1__* td_proc; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_pid; int /*<<< orphan*/  p_comm; } ;

/* Variables and functions */
 int umtx_handle_rb (struct thread*,uintptr_t,uintptr_t*,int) ; 
 int umtx_max_rb ; 
 int umtx_read_uptr (struct thread*,uintptr_t,uintptr_t*) ; 
 scalar_t__ umtx_verbose_rb ; 
 int /*<<< orphan*/  uprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
umtx_cleanup_rb_list(struct thread *td, uintptr_t rb_list, uintptr_t *rb_inact,
    const char *name)
{
	int error, i;
	uintptr_t rbp;
	bool inact;

	if (rb_list == 0)
		return;
	error = umtx_read_uptr(td, rb_list, &rbp);
	for (i = 0; error == 0 && rbp != 0 && i < umtx_max_rb; i++) {
		if (rbp == *rb_inact) {
			inact = true;
			*rb_inact = 0;
		} else
			inact = false;
		error = umtx_handle_rb(td, rbp, &rbp, inact);
	}
	if (i == umtx_max_rb && umtx_verbose_rb) {
		uprintf("comm %s pid %d: reached umtx %smax rb %d\n",
		    td->td_proc->p_comm, td->td_proc->p_pid, name, umtx_max_rb);
	}
	if (error != 0 && umtx_verbose_rb) {
		uprintf("comm %s pid %d: handling %srb error %d\n",
		    td->td_proc->p_comm, td->td_proc->p_pid, name, error);
	}
}