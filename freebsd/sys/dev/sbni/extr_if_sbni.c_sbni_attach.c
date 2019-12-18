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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int u_char ;
struct sbni_softc {int cur_rxl_index; scalar_t__ delta_rxl; int /*<<< orphan*/  enaddr; int /*<<< orphan*/  lock; int /*<<< orphan*/  wch; struct ifnet* ifp; } ;
struct sbni_flags {int rate; } ;
struct ifnet {int if_baudrate; int if_flags; int /*<<< orphan*/  if_xname; int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_init; struct sbni_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR0 ; 
 int ENOMEM ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,char*,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sbni_inb (struct sbni_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbni_init ; 
 int /*<<< orphan*/  sbni_ioctl ; 
 int /*<<< orphan*/  sbni_outb (struct sbni_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbni_start ; 
 int /*<<< orphan*/  set_initial_values (struct sbni_softc*,struct sbni_flags) ; 

int
sbni_attach(struct sbni_softc *sc, int unit, struct sbni_flags flags)
{
	struct ifnet *ifp;
	u_char csr0;
   
	ifp = sc->ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL)
		return (ENOMEM);
	sbni_outb(sc, CSR0, 0);
	set_initial_values(sc, flags);

	/* Initialize ifnet structure */
	ifp->if_softc	= sc;
	if_initname(ifp, "sbni", unit);
	ifp->if_init	= sbni_init;
	ifp->if_start	= sbni_start;
	ifp->if_ioctl	= sbni_ioctl;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifqmaxlen);

	/* report real baud rate */
	csr0 = sbni_inb(sc, CSR0);
	ifp->if_baudrate =
		(csr0 & 0x01 ? 500000 : 2000000) / (1 << flags.rate);

	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;

	mtx_init(&sc->lock, ifp->if_xname, MTX_NETWORK_LOCK, MTX_DEF);
	callout_init_mtx(&sc->wch, &sc->lock, 0);
	ether_ifattach(ifp, sc->enaddr);
	/* device attach does transition from UNCONFIGURED to IDLE state */

	if_printf(ifp, "speed %ju, rxl ", (uintmax_t)ifp->if_baudrate);
	if (sc->delta_rxl)
		printf("auto\n");
	else
		printf("%d (fixed)\n", sc->cur_rxl_index);
	return (0);
}