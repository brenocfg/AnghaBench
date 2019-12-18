#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cuse_server {scalar_t__ is_closing; int /*<<< orphan*/  cv; int /*<<< orphan*/  head; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tqe_prev; } ;
struct TYPE_4__ {unsigned long fflags; uintptr_t data_pointer; unsigned long argument; } ;
struct cuse_client_command {TYPE_3__* client; TYPE_2__ entry; TYPE_1__ sub; } ;
struct TYPE_6__ {struct cuse_server* server; } ;

/* Variables and functions */
 scalar_t__ CUSE_CLIENT_CLOSING (TYPE_3__*) ; 
 unsigned long CUSE_FFLAG_COMPAT32 ; 
 unsigned long CUSE_FFLAG_NONBLOCK ; 
 unsigned long CUSE_FFLAG_READ ; 
 unsigned long CUSE_FFLAG_WRITE ; 
 int FREAD ; 
 int FWRITE ; 
 int IO_NDELAY ; 
 scalar_t__ SV_CURPROC_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cuse_client_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry ; 

__attribute__((used)) static void
cuse_client_send_command_locked(struct cuse_client_command *pccmd,
    uintptr_t data_ptr, unsigned long arg, int fflags, int ioflag)
{
	unsigned long cuse_fflags = 0;
	struct cuse_server *pcs;

	if (fflags & FREAD)
		cuse_fflags |= CUSE_FFLAG_READ;

	if (fflags & FWRITE)
		cuse_fflags |= CUSE_FFLAG_WRITE;

	if (ioflag & IO_NDELAY)
		cuse_fflags |= CUSE_FFLAG_NONBLOCK;
#if defined(__LP64__)
	if (SV_CURPROC_FLAG(SV_ILP32))
		cuse_fflags |= CUSE_FFLAG_COMPAT32;
#endif
	pccmd->sub.fflags = cuse_fflags;
	pccmd->sub.data_pointer = data_ptr;
	pccmd->sub.argument = arg;

	pcs = pccmd->client->server;

	if ((pccmd->entry.tqe_prev == NULL) &&
	    (CUSE_CLIENT_CLOSING(pccmd->client) == 0) &&
	    (pcs->is_closing == 0)) {
		TAILQ_INSERT_TAIL(&pcs->head, pccmd, entry);
		cv_signal(&pcs->cv);
	}
}