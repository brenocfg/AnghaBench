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
struct msgbuf {int /*<<< orphan*/  msg_lock; int /*<<< orphan*/  msg_wseq; } ;

/* Variables and functions */
 int /*<<< orphan*/  msgbuf_do_addchar (struct msgbuf*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

void
msgbuf_addchar(struct msgbuf *mbp, int c)
{
	mtx_lock_spin(&mbp->msg_lock);

	msgbuf_do_addchar(mbp, &mbp->msg_wseq, c);

	mtx_unlock_spin(&mbp->msg_lock);
}