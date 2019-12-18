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
struct ksem_open_args {int oflag; int /*<<< orphan*/  value; int /*<<< orphan*/  mode; int /*<<< orphan*/  idp; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (char*) ; 
 int EINVAL ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int ksem_create (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
sys_ksem_open(struct thread *td, struct ksem_open_args *uap)
{

	DP((">>> ksem_open start, pid=%d\n", (int)td->td_proc->p_pid));

	if ((uap->oflag & ~(O_CREAT | O_EXCL)) != 0)
		return (EINVAL);
	return (ksem_create(td, uap->name, uap->idp, uap->mode, uap->value,
	    uap->oflag, 0));
}