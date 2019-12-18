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
struct sockbuf {int sb_flags; int /*<<< orphan*/  sb_aiojobq; } ;
struct socket {struct sockbuf so_snd; struct sockbuf so_rcv; TYPE_2__* so_proto; } ;
struct TYPE_6__ {int aio_lio_opcode; } ;
struct kaiocb {TYPE_3__ uaiocb; } ;
struct file {struct socket* f_data; } ;
struct TYPE_5__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_4__ {int (* pru_aio_queue ) (struct socket*,struct kaiocb*) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  LIO_READ 129 
#define  LIO_WRITE 128 
 int SB_AIO ; 
 int SB_AIO_RUNNING ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (struct sockbuf*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (struct sockbuf*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct kaiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_set_cancel_function (struct kaiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ soaio_ready (struct socket*,struct sockbuf*) ; 
 int /*<<< orphan*/  soo_aio_cancel ; 
 int /*<<< orphan*/  sowakeup_aio (struct socket*,struct sockbuf*) ; 
 int stub1 (struct socket*,struct kaiocb*) ; 

__attribute__((used)) static int
soo_aio_queue(struct file *fp, struct kaiocb *job)
{
	struct socket *so;
	struct sockbuf *sb;
	int error;

	so = fp->f_data;
	error = (*so->so_proto->pr_usrreqs->pru_aio_queue)(so, job);
	if (error == 0)
		return (0);

	switch (job->uaiocb.aio_lio_opcode) {
	case LIO_READ:
		sb = &so->so_rcv;
		break;
	case LIO_WRITE:
		sb = &so->so_snd;
		break;
	default:
		return (EINVAL);
	}

	SOCKBUF_LOCK(sb);
	if (!aio_set_cancel_function(job, soo_aio_cancel))
		panic("new job was cancelled");
	TAILQ_INSERT_TAIL(&sb->sb_aiojobq, job, list);
	if (!(sb->sb_flags & SB_AIO_RUNNING)) {
		if (soaio_ready(so, sb))
			sowakeup_aio(so, sb);
		else
			sb->sb_flags |= SB_AIO;
	}
	SOCKBUF_UNLOCK(sb);
	return (0);
}