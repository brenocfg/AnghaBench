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
struct unpcb {struct socket* unp_socket; struct unpcb* unp_conn; } ;
struct socket {int /*<<< orphan*/  so_rcv; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNP_PCB_LOCK (struct unpcb*) ; 
 scalar_t__ UNP_PCB_TRYLOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK (struct unpcb*) ; 
 struct mbuf* m_free (struct mbuf*) ; 
 int sbready (int /*<<< orphan*/ *,struct mbuf*,int) ; 
 int /*<<< orphan*/  sorwakeup_locked (struct socket*) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  unp_pcb_hold (struct unpcb*) ; 
 scalar_t__ unp_pcb_rele (struct unpcb*) ; 

__attribute__((used)) static int
uipc_ready(struct socket *so, struct mbuf *m, int count)
{
	struct unpcb *unp, *unp2;
	struct socket *so2;
	int error;

	unp = sotounpcb(so);

	UNP_PCB_LOCK(unp);
	if ((unp2 = unp->unp_conn) == NULL) {
		UNP_PCB_UNLOCK(unp);
		goto error;
	}
	if (unp != unp2) {
		if (UNP_PCB_TRYLOCK(unp2) == 0) {
			unp_pcb_hold(unp2);
			UNP_PCB_UNLOCK(unp);
			UNP_PCB_LOCK(unp2);
			if (unp_pcb_rele(unp2))
				goto error;
		} else
			UNP_PCB_UNLOCK(unp);
	}
	so2 = unp2->unp_socket;

	SOCKBUF_LOCK(&so2->so_rcv);
	if ((error = sbready(&so2->so_rcv, m, count)) == 0)
		sorwakeup_locked(so2);
	else
		SOCKBUF_UNLOCK(&so2->so_rcv);

	UNP_PCB_UNLOCK(unp2);

	return (error);
 error:
	for (int i = 0; i < count; i++)
		m = m_free(m);
	return (ECONNRESET);
}