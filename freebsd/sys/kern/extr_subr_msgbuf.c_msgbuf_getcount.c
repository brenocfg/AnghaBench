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
typedef  scalar_t__ u_int ;
struct msgbuf {scalar_t__ msg_size; int /*<<< orphan*/  msg_rseq; int /*<<< orphan*/  msg_wseq; } ;

/* Variables and functions */
 scalar_t__ MSGBUF_SEQSUB (struct msgbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
msgbuf_getcount(struct msgbuf *mbp)
{
	u_int len;

	len = MSGBUF_SEQSUB(mbp, mbp->msg_wseq, mbp->msg_rseq);
	if (len > mbp->msg_size)
		len = mbp->msg_size;
	return (len);
}