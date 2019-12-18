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
struct cdev {int dummy; } ;
struct audit_pipe {int /*<<< orphan*/  ap_sigio; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct audit_pipe* audit_pipe_alloc () ; 
 int /*<<< orphan*/  audit_pipe_dtor (struct audit_pipe*) ; 
 int devfs_set_cdevpriv (struct audit_pipe*,int /*<<< orphan*/  (*) (struct audit_pipe*)) ; 
 int /*<<< orphan*/  fsetown (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
audit_pipe_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
	struct audit_pipe *ap;
	int error;

	ap = audit_pipe_alloc();
	if (ap == NULL)
		return (ENOMEM);
	fsetown(td->td_proc->p_pid, &ap->ap_sigio);
	error = devfs_set_cdevpriv(ap, audit_pipe_dtor);
	if (error != 0)
		audit_pipe_dtor(ap);
	return (error);
}