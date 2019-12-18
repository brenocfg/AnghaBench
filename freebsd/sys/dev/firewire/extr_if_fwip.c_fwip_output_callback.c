#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ifq_head; } ;
struct ifnet {TYPE_1__ if_snd; } ;
struct TYPE_4__ {struct ifnet* fwip_ifp; } ;
struct fwip_softc {int /*<<< orphan*/  xferlist; TYPE_2__ fw_softc; } ;
struct fw_xfer {scalar_t__ resp; int /*<<< orphan*/  mbuf; scalar_t__ sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWIPDEBUG (struct ifnet*,char*,scalar_t__) ; 
 int /*<<< orphan*/  FWIP_LOCK (struct fwip_softc*) ; 
 int /*<<< orphan*/  FWIP_UNLOCK (struct fwip_softc*) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fw_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_xfer_unload (struct fw_xfer*) ; 
 int /*<<< orphan*/  fwip_start (struct ifnet*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void
fwip_output_callback(struct fw_xfer *xfer)
{
	struct fwip_softc *fwip;
	struct ifnet *ifp;
	int s;

	fwip = (struct fwip_softc *)xfer->sc;
	ifp = fwip->fw_softc.fwip_ifp;
	/* XXX error check */
	FWIPDEBUG(ifp, "resp = %d\n", xfer->resp);
	if (xfer->resp != 0)
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	m_freem(xfer->mbuf);
	fw_xfer_unload(xfer);

	s = splimp();
	FWIP_LOCK(fwip);
	STAILQ_INSERT_TAIL(&fwip->xferlist, xfer, link);
	FWIP_UNLOCK(fwip);
	splx(s);

	/* for queue full */
	if (ifp->if_snd.ifq_head != NULL) {
		fwip_start(ifp);
	}
}