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
typedef  int u_int32_t ;
struct ifnet {int dummy; } ;
struct TYPE_2__ {unsigned int rb_rdtail; int /*<<< orphan*/  rb_rxd; } ;
struct hme_softc {int sc_flags; TYPE_1__ sc_rb; int /*<<< orphan*/  sc_cdmamap; int /*<<< orphan*/  sc_cdmatag; int /*<<< orphan*/  sc_dev; struct ifnet* sc_ifp; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 unsigned int HME_NRXDESC ; 
 int HME_PCI ; 
 unsigned int HME_XD_DECODE_RSIZE (int) ; 
 int HME_XD_GETFLAGS (int,int /*<<< orphan*/ ,unsigned int) ; 
 int HME_XD_OFL ; 
 int HME_XD_OWN ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  KTR_HME ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  hme_discard_rxbuf (struct hme_softc*,unsigned int) ; 
 int /*<<< orphan*/  hme_read (struct hme_softc*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hme_rint(struct hme_softc *sc)
{
	caddr_t xdr = sc->sc_rb.rb_rxd;
	struct ifnet *ifp = sc->sc_ifp;
	unsigned int ri, len;
	int progress = 0;
	u_int32_t flags;

	/*
	 * Process all buffers with valid data.
	 */
	bus_dmamap_sync(sc->sc_cdmatag, sc->sc_cdmamap, BUS_DMASYNC_POSTREAD);
	for (ri = sc->sc_rb.rb_rdtail;; ri = (ri + 1) % HME_NRXDESC) {
		flags = HME_XD_GETFLAGS(sc->sc_flags & HME_PCI, xdr, ri);
		CTR2(KTR_HME, "hme_rint: index %d, flags %#x", ri, flags);
		if ((flags & HME_XD_OWN) != 0)
			break;

		progress++;
		if ((flags & HME_XD_OFL) != 0) {
			device_printf(sc->sc_dev, "buffer overflow, ri=%d; "
			    "flags=0x%x\n", ri, flags);
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			hme_discard_rxbuf(sc, ri);
		} else {
			len = HME_XD_DECODE_RSIZE(flags);
			hme_read(sc, ri, len, flags);
		}
	}
	if (progress) {
		bus_dmamap_sync(sc->sc_cdmatag, sc->sc_cdmamap,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	}
	sc->sc_rb.rb_rdtail = ri;
}