#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ic_softc {int ic_flags; char* ic_obuf; char* ic_ifbuf; int /*<<< orphan*/  ic_lock; TYPE_1__* ic_ifp; } ;
struct TYPE_2__ {int if_mtu; } ;

/* Variables and functions */
 scalar_t__ ICHDRLEN ; 
 int IC_BUFFERS_BUSY ; 
 int IC_BUFFER_WAITER ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (struct ic_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ic_alloc_buffers(struct ic_softc *sc, int mtu)
{
	char *obuf, *ifbuf;

	obuf = malloc(mtu + ICHDRLEN, M_DEVBUF, M_WAITOK);
	ifbuf = malloc(mtu + ICHDRLEN, M_DEVBUF, M_WAITOK);

	mtx_lock(&sc->ic_lock);
	while (sc->ic_flags & IC_BUFFERS_BUSY) {
		sc->ic_flags |= IC_BUFFER_WAITER;
		mtx_sleep(sc, &sc->ic_lock, 0, "icalloc", 0);
		sc->ic_flags &= ~IC_BUFFER_WAITER;
	}

	free(sc->ic_obuf, M_DEVBUF);
	free(sc->ic_ifbuf, M_DEVBUF);
	sc->ic_obuf = obuf;
	sc->ic_ifbuf = ifbuf;
	sc->ic_ifp->if_mtu = mtu;
	mtx_unlock(&sc->ic_lock);
}