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
struct msgbuf {scalar_t__ msg_cksum; scalar_t__ msg_rseq; scalar_t__ msg_wseq; int /*<<< orphan*/  msg_size; int /*<<< orphan*/  msg_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
msgbuf_clear(struct msgbuf *mbp)
{

	bzero(mbp->msg_ptr, mbp->msg_size);
	mbp->msg_wseq = 0;
	mbp->msg_rseq = 0;
	mbp->msg_cksum = 0;
}