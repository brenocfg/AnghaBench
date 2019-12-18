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
struct mbuf {int dummy; } ;
struct TYPE_2__ {scalar_t__ ifq_len; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; TYPE_1__ if_snd; scalar_t__ if_softc; } ;
struct fwe_softc {scalar_t__ dma_ch; } ;
struct fwe_eth_softc {struct fwe_softc* fwe; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWEDEBUG (struct ifnet*,char*) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IF_DEQUEUE (TYPE_1__*,struct mbuf*) ; 
 int /*<<< orphan*/  fwe_as_output (struct fwe_softc*,struct ifnet*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void
fwe_start(struct ifnet *ifp)
{
	struct fwe_softc *fwe = ((struct fwe_eth_softc *)ifp->if_softc)->fwe;
	int s;

	FWEDEBUG(ifp, "starting\n");

	if (fwe->dma_ch < 0) {
		struct mbuf	*m = NULL;

		FWEDEBUG(ifp, "not ready\n");

		s = splimp();
		do {
			IF_DEQUEUE(&ifp->if_snd, m);
			if (m != NULL)
				m_freem(m);
			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		} while (m != NULL);
		splx(s);

		return;
	}

	s = splimp();
	ifp->if_drv_flags |= IFF_DRV_OACTIVE;

	if (ifp->if_snd.ifq_len != 0)
		fwe_as_output(fwe, ifp);

	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
	splx(s);
}