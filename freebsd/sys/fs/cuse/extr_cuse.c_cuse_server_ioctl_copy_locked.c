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
typedef  scalar_t__ uint32_t ;
struct proc {int dummy; } ;
struct cuse_data_chunk {scalar_t__ peer_ptr; scalar_t__ length; scalar_t__ local_ptr; } ;
struct cuse_client_command {scalar_t__ proc_refs; int /*<<< orphan*/  cv; struct proc* proc_curr; TYPE_1__* client; } ;
struct TYPE_2__ {scalar_t__ ioctl_buffer; } ;

/* Variables and functions */
 scalar_t__ CUSE_BUFFER_MAX ; 
 scalar_t__ CUSE_BUF_MIN_PTR ; 
 int EFAULT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int copyin (void*,scalar_t__,scalar_t__) ; 
 int copyout (scalar_t__,void*,scalar_t__) ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cuse_server_ioctl_copy_locked(struct cuse_client_command *pccmd,
    struct cuse_data_chunk *pchk, int isread)
{
	struct proc *p_proc;
	uint32_t offset;
	int error;

	offset = pchk->peer_ptr - CUSE_BUF_MIN_PTR;

	if (pchk->length > CUSE_BUFFER_MAX)
		return (EFAULT);

	if (offset >= CUSE_BUFFER_MAX)
		return (EFAULT);

	if ((offset + pchk->length) > CUSE_BUFFER_MAX)
		return (EFAULT);

	p_proc = pccmd->proc_curr;
	if (p_proc == NULL)
		return (ENXIO);

	if (pccmd->proc_refs < 0)
		return (ENOMEM);

	pccmd->proc_refs++;

	cuse_unlock();

	if (isread == 0) {
		error = copyin(
		    (void *)pchk->local_ptr,
		    pccmd->client->ioctl_buffer + offset,
		    pchk->length);
	} else {
		error = copyout(
		    pccmd->client->ioctl_buffer + offset,
		    (void *)pchk->local_ptr,
		    pchk->length);
	}

	cuse_lock();

	pccmd->proc_refs--;

	if (pccmd->proc_curr == NULL)
		cv_signal(&pccmd->cv);

	return (error);
}