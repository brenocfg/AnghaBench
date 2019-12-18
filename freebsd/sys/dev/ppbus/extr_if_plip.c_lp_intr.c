#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_char ;
struct mbuf {int dummy; } ;
struct lp_data {size_t* sc_ifbuf; scalar_t__ sc_iferrs; TYPE_1__* sc_ifp; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int if_flags; int if_mtu; int /*<<< orphan*/  if_drv_flags; int /*<<< orphan*/  if_fib; int /*<<< orphan*/  if_bpf; } ;

/* Variables and functions */
 int CLPIPHDRLEN ; 
 int /*<<< orphan*/  IFCOUNTER_IBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_LINK0 ; 
 int LPIPHDRLEN ; 
 int LPIP_SHAKE ; 
 scalar_t__ LPMAXERRS ; 
 int LPMAXSPIN2 ; 
 int MLPIPHDRLEN ; 
 int /*<<< orphan*/  M_SETFIB (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETISR_IP ; 
 scalar_t__ bpf_peers_present (int /*<<< orphan*/ ) ; 
 int clpinbyte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  lprintf (char*) ; 
 int /*<<< orphan*/  lptap (TYPE_1__*,struct mbuf*) ; 
 struct mbuf* m_devget (size_t*,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netisr_queue (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  ppb_assert_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int ppb_rstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppb_wdtr (int /*<<< orphan*/ ,int) ; 
 int* trecvh ; 
 int* trecvl ; 

__attribute__((used)) static void
lp_intr(void *arg)
{
	struct lp_data *sc = arg;
	device_t ppbus = device_get_parent(sc->sc_dev);
	int len, j;
	u_char *bp;
	u_char c, cl;
	struct mbuf *top;

	ppb_assert_locked(ppbus);
	if (sc->sc_ifp->if_flags & IFF_LINK0) {

		/* Ack. the request */
		ppb_wdtr(ppbus, 0x01);

		/* Get the packet length */
		j = clpinbyte(LPMAXSPIN2, ppbus);
		if (j == -1)
			goto err;
		len = j;
		j = clpinbyte(LPMAXSPIN2, ppbus);
		if (j == -1)
			goto err;
		len = len + (j << 8);
		if (len > sc->sc_ifp->if_mtu + MLPIPHDRLEN)
			goto err;

		bp = sc->sc_ifbuf;

		while (len--) {
			j = clpinbyte(LPMAXSPIN2, ppbus);
			if (j == -1) {
				goto err;
			}
			*bp++ = j;
		}

		/* Get and ignore checksum */
		j = clpinbyte(LPMAXSPIN2, ppbus);
		if (j == -1) {
			goto err;
		}

		len = bp - sc->sc_ifbuf;
		if (len <= CLPIPHDRLEN)
			goto err;

		sc->sc_iferrs = 0;

		len -= CLPIPHDRLEN;
		if_inc_counter(sc->sc_ifp, IFCOUNTER_IPACKETS, 1);
		if_inc_counter(sc->sc_ifp, IFCOUNTER_IBYTES, len);
		top = m_devget(sc->sc_ifbuf + CLPIPHDRLEN, len, 0, sc->sc_ifp,
		    0);
		if (top) {
			ppb_unlock(ppbus);
			if (bpf_peers_present(sc->sc_ifp->if_bpf))
				lptap(sc->sc_ifp, top);

			M_SETFIB(top, sc->sc_ifp->if_fib);

			/* mbuf is free'd on failure. */
			netisr_queue(NETISR_IP, top);
			ppb_lock(ppbus);
		}
		return;
	}
	while ((ppb_rstr(ppbus) & LPIP_SHAKE)) {
		len = sc->sc_ifp->if_mtu + LPIPHDRLEN;
		bp  = sc->sc_ifbuf;
		while (len--) {

			cl = ppb_rstr(ppbus);
			ppb_wdtr(ppbus, 8);

			j = LPMAXSPIN2;
			while ((ppb_rstr(ppbus) & LPIP_SHAKE))
				if (!--j)
					goto err;

			c = ppb_rstr(ppbus);
			ppb_wdtr(ppbus, 0);

			*bp++= trecvh[cl] | trecvl[c];

			j = LPMAXSPIN2;
			while (!((cl = ppb_rstr(ppbus)) & LPIP_SHAKE)) {
				if (cl != c &&
				    (((cl = ppb_rstr(ppbus)) ^ 0xb8) & 0xf8) ==
				    (c & 0xf8))
					goto end;
				if (!--j)
					goto err;
			}
		}

	end:
		len = bp - sc->sc_ifbuf;
		if (len <= LPIPHDRLEN)
			goto err;

		sc->sc_iferrs = 0;

		len -= LPIPHDRLEN;
		if_inc_counter(sc->sc_ifp, IFCOUNTER_IPACKETS, 1);
		if_inc_counter(sc->sc_ifp, IFCOUNTER_IBYTES, len);
		top = m_devget(sc->sc_ifbuf + LPIPHDRLEN, len, 0, sc->sc_ifp,
		    0);
		if (top) {
			ppb_unlock(ppbus);
			if (bpf_peers_present(sc->sc_ifp->if_bpf))
				lptap(sc->sc_ifp, top);

			M_SETFIB(top, sc->sc_ifp->if_fib);

			/* mbuf is free'd on failure. */
			netisr_queue(NETISR_IP, top);
			ppb_lock(ppbus);
		}
	}
	return;

err:
	ppb_wdtr(ppbus, 0);
	lprintf("R");
	if_inc_counter(sc->sc_ifp, IFCOUNTER_IERRORS, 1);
	sc->sc_iferrs++;

	/*
	 * We are not able to send receive anything for now,
	 * so stop wasting our time
	 */
	if (sc->sc_iferrs > LPMAXERRS) {
		if_printf(sc->sc_ifp, "Too many errors, Going off-line.\n");
		ppb_wctr(ppbus, 0x00);
		sc->sc_ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		sc->sc_iferrs = 0;
	}
}