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
struct proc {int dummy; } ;
struct cuse_data_chunk {int /*<<< orphan*/  length; int /*<<< orphan*/  local_ptr; int /*<<< orphan*/  peer_ptr; } ;
struct cuse_client_command {scalar_t__ proc_refs; int /*<<< orphan*/  cv; struct proc* proc_curr; } ;
struct TYPE_2__ {struct proc* td_proc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int cuse_proc2proc_copy (struct proc*,int /*<<< orphan*/ ,struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cuse_server_data_copy_locked(struct cuse_client_command *pccmd,
    struct cuse_data_chunk *pchk, int isread)
{
	struct proc *p_proc;
	int error;

	p_proc = pccmd->proc_curr;
	if (p_proc == NULL)
		return (ENXIO);

	if (pccmd->proc_refs < 0)
		return (ENOMEM);

	pccmd->proc_refs++;

	cuse_unlock();

	if (isread == 0) {
		error = cuse_proc2proc_copy(
		    curthread->td_proc, pchk->local_ptr,
		    p_proc, pchk->peer_ptr,
		    pchk->length);
	} else {
		error = cuse_proc2proc_copy(
		    p_proc, pchk->peer_ptr,
		    curthread->td_proc, pchk->local_ptr,
		    pchk->length);
	}

	cuse_lock();

	pccmd->proc_refs--;

	if (pccmd->proc_curr == NULL)
		cv_signal(&pccmd->cv);

	return (error);
}