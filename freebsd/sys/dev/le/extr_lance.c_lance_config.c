#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lance_softc {int sc_nsupmedia; int sc_memsize; int sc_nrbuf; int sc_ntbuf; int /*<<< orphan*/  sc_media; int /*<<< orphan*/  sc_defaultmedia; int /*<<< orphan*/ * sc_supmedia; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_wdog_ch; struct ifnet* sc_ifp; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifq_drv_maxlen; } ;
struct ifnet {int if_flags; TYPE_1__ if_snd; int /*<<< orphan*/  if_baudrate; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; struct lance_softc* if_softc; } ;

/* Variables and functions */
 int ENOSPC ; 
 int ENXIO ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_MAKEWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFM_MANUAL ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  IF_Mbps (int) ; 
 int LEBLEN ; 
 int /*<<< orphan*/  LE_LOCK (struct lance_softc*) ; 
 scalar_t__ LE_LOCK_INITIALIZED (struct lance_softc*) ; 
 int /*<<< orphan*/  LE_UNLOCK (struct lance_softc*) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,char const*,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,int,int) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  lance_init ; 
 int /*<<< orphan*/  lance_ioctl ; 
 int /*<<< orphan*/  lance_mediachange ; 
 int /*<<< orphan*/  lance_mediastatus ; 
 int /*<<< orphan*/  lance_start ; 
 int /*<<< orphan*/  lance_stop (struct lance_softc*) ; 

int
lance_config(struct lance_softc *sc, const char* name, int unit)
{
	struct ifnet *ifp;
	int i, nbuf;

	if (LE_LOCK_INITIALIZED(sc) == 0)
		return (ENXIO);

	ifp = sc->sc_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL)
		return (ENOSPC);

	callout_init_mtx(&sc->sc_wdog_ch, &sc->sc_mtx, 0);

	/* Initialize ifnet structure. */
	ifp->if_softc = sc;
	if_initname(ifp, name, unit);
	ifp->if_start = lance_start;
	ifp->if_ioctl = lance_ioctl;
	ifp->if_init = lance_init;
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
#ifdef LANCE_REVC_BUG
	ifp->if_flags &= ~IFF_MULTICAST;
#endif
	ifp->if_baudrate = IF_Mbps(10);
	IFQ_SET_MAXLEN(&ifp->if_snd, ifqmaxlen);
	ifp->if_snd.ifq_drv_maxlen = ifqmaxlen;
	IFQ_SET_READY(&ifp->if_snd);

	/* Initialize ifmedia structures. */
	ifmedia_init(&sc->sc_media, 0, lance_mediachange, lance_mediastatus);
	if (sc->sc_supmedia != NULL) {
		for (i = 0; i < sc->sc_nsupmedia; i++)
			ifmedia_add(&sc->sc_media, sc->sc_supmedia[i], 0, NULL);
		ifmedia_set(&sc->sc_media, sc->sc_defaultmedia);
	} else {
		ifmedia_add(&sc->sc_media,
		    IFM_MAKEWORD(IFM_ETHER, IFM_MANUAL, 0, 0), 0, NULL);
		ifmedia_set(&sc->sc_media,
		    IFM_MAKEWORD(IFM_ETHER, IFM_MANUAL, 0, 0));
	}

	switch (sc->sc_memsize) {
	case 8192:
		sc->sc_nrbuf = 4;
		sc->sc_ntbuf = 1;
		break;
	case 16384:
		sc->sc_nrbuf = 8;
		sc->sc_ntbuf = 2;
		break;
	case 32768:
		sc->sc_nrbuf = 16;
		sc->sc_ntbuf = 4;
		break;
	case 65536:
		sc->sc_nrbuf = 32;
		sc->sc_ntbuf = 8;
		break;
	case 131072:
		sc->sc_nrbuf = 64;
		sc->sc_ntbuf = 16;
		break;
	case 262144:
		sc->sc_nrbuf = 128;
		sc->sc_ntbuf = 32;
		break;
	default:
		/* weird memory size; cope with it */
		nbuf = sc->sc_memsize / LEBLEN;
		sc->sc_ntbuf = nbuf / 5;
		sc->sc_nrbuf = nbuf - sc->sc_ntbuf;
	}

	if_printf(ifp, "%d receive buffers, %d transmit buffers\n",
	    sc->sc_nrbuf, sc->sc_ntbuf);

	/* Make sure the chip is stopped. */
	LE_LOCK(sc);
	lance_stop(sc);
	LE_UNLOCK(sc);

	return (0);
}