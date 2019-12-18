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
struct msgbuf {int /*<<< orphan*/  bufs; } ;
struct ibuf {scalar_t__ rpos; scalar_t__ wpos; } ;

/* Variables and functions */
 struct ibuf* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct ibuf* TAILQ_NEXT (struct ibuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  ibuf_dequeue (struct msgbuf*,struct ibuf*) ; 

void
msgbuf_drain(struct msgbuf *msgbuf, size_t n)
{
	struct ibuf	*buf, *next;

	for (buf = TAILQ_FIRST(&msgbuf->bufs); buf != NULL && n > 0;
	    buf = next) {
		next = TAILQ_NEXT(buf, entry);
		if (buf->rpos + n >= buf->wpos) {
			n -= buf->wpos - buf->rpos;
			ibuf_dequeue(msgbuf, buf);
		} else {
			buf->rpos += n;
			n = 0;
		}
	}
}