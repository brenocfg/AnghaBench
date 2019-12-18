#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockbuf {int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_aiojobq; } ;
struct socket {struct sockbuf so_snd; struct sockbuf so_rcv; } ;
struct TYPE_4__ {int aio_lio_opcode; } ;
struct kaiocb {long aio_done; TYPE_2__ uaiocb; TYPE_1__* fd_file; } ;
struct TYPE_3__ {struct socket* f_data; } ;

/* Variables and functions */
 int LIO_READ ; 
 int LIO_WRITE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  SB_AIO ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (struct sockbuf*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (struct sockbuf*) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct kaiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_cancel (struct kaiocb*) ; 
 int /*<<< orphan*/  aio_cancel_cleared (struct kaiocb*) ; 
 int /*<<< orphan*/  aio_complete (struct kaiocb*,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 

__attribute__((used)) static void
soo_aio_cancel(struct kaiocb *job)
{
	struct socket *so;
	struct sockbuf *sb;
	long done;
	int opcode;

	so = job->fd_file->f_data;
	opcode = job->uaiocb.aio_lio_opcode;
	if (opcode == LIO_READ)
		sb = &so->so_rcv;
	else {
		MPASS(opcode == LIO_WRITE);
		sb = &so->so_snd;
	}

	SOCKBUF_LOCK(sb);
	if (!aio_cancel_cleared(job))
		TAILQ_REMOVE(&sb->sb_aiojobq, job, list);
	if (TAILQ_EMPTY(&sb->sb_aiojobq))
		sb->sb_flags &= ~SB_AIO;
	SOCKBUF_UNLOCK(sb);

	done = job->aio_done;
	if (done != 0)
		aio_complete(job, done, 0);
	else
		aio_cancel(job);
}