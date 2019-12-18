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
struct socket {int /*<<< orphan*/  so_vnet; } ;
struct sockbuf {int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_aiojobq; } ;
struct kaiocb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_AIO ; 
 int /*<<< orphan*/  SB_AIO_RUNNING ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (struct sockbuf*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (struct sockbuf*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct kaiocb* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct kaiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_clear_cancel_function (struct kaiocb*) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  soaio_process_job (struct socket*,struct sockbuf*,struct kaiocb*) ; 
 scalar_t__ soaio_ready (struct socket*,struct sockbuf*) ; 
 int /*<<< orphan*/  sorele (struct socket*) ; 

__attribute__((used)) static void
soaio_process_sb(struct socket *so, struct sockbuf *sb)
{
	struct kaiocb *job;

	CURVNET_SET(so->so_vnet);
	SOCKBUF_LOCK(sb);
	while (!TAILQ_EMPTY(&sb->sb_aiojobq) && soaio_ready(so, sb)) {
		job = TAILQ_FIRST(&sb->sb_aiojobq);
		TAILQ_REMOVE(&sb->sb_aiojobq, job, list);
		if (!aio_clear_cancel_function(job))
			continue;

		soaio_process_job(so, sb, job);
	}

	/*
	 * If there are still pending requests, the socket must not be
	 * ready so set SB_AIO to request a wakeup when the socket
	 * becomes ready.
	 */
	if (!TAILQ_EMPTY(&sb->sb_aiojobq))
		sb->sb_flags |= SB_AIO;
	sb->sb_flags &= ~SB_AIO_RUNNING;
	SOCKBUF_UNLOCK(sb);

	SOCK_LOCK(so);
	sorele(so);
	CURVNET_RESTORE();
}