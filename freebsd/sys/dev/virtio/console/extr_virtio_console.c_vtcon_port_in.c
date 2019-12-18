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
typedef  int uint32_t ;
struct vtcon_port {int vtcport_flags; int /*<<< orphan*/  vtcport_alt_break_state; struct virtqueue* vtcport_invq; struct tty* vtcport_tty; } ;
struct virtqueue {int dummy; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int VTCON_PORT_FLAG_CONSOLE ; 
 int /*<<< orphan*/  kdb_alt_break (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 char* virtqueue_dequeue (struct virtqueue*,int*) ; 
 scalar_t__ virtqueue_enable_intr (struct virtqueue*) ; 
 int /*<<< orphan*/  virtqueue_notify (struct virtqueue*) ; 
 int /*<<< orphan*/  vtcon_port_requeue_buf (struct vtcon_port*,char*) ; 

__attribute__((used)) static void
vtcon_port_in(struct vtcon_port *port)
{
	struct virtqueue *vq;
	struct tty *tp;
	char *buf;
	uint32_t len;
	int i, deq;

	tp = port->vtcport_tty;
	vq = port->vtcport_invq;

again:
	deq = 0;

	while ((buf = virtqueue_dequeue(vq, &len)) != NULL) {
		for (i = 0; i < len; i++) {
#if defined(KDB)
			if (port->vtcport_flags & VTCON_PORT_FLAG_CONSOLE)
				kdb_alt_break(buf[i],
				    &port->vtcport_alt_break_state);
#endif
			ttydisc_rint(tp, buf[i], 0);
		}
		vtcon_port_requeue_buf(port, buf);
		deq++;
	}
	ttydisc_rint_done(tp);

	if (deq > 0)
		virtqueue_notify(vq);

	if (virtqueue_enable_intr(vq) != 0)
		goto again;
}