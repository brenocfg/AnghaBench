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
struct msgbuf {int msg_size; int msg_lastpri; int /*<<< orphan*/  msg_lock; scalar_t__ msg_flags; int /*<<< orphan*/  msg_magic; int /*<<< orphan*/  msg_seqmod; void* msg_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_MAGIC ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  SEQMOD (int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msgbuf_clear (struct msgbuf*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
msgbuf_init(struct msgbuf *mbp, void *ptr, int size)
{

	mbp->msg_ptr = ptr;
	mbp->msg_size = size;
	mbp->msg_seqmod = SEQMOD(size);
	msgbuf_clear(mbp);
	mbp->msg_magic = MSG_MAGIC;
	mbp->msg_lastpri = -1;
	mbp->msg_flags = 0;
	bzero(&mbp->msg_lock, sizeof(mbp->msg_lock));
	mtx_init(&mbp->msg_lock, "msgbuf", NULL, MTX_SPIN);
}