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
struct usb_ether {int dummy; } ;
struct ifnet {int dummy; } ;
struct cue_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUE_LOCK_ASSERT (struct cue_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CUE_RX_FRAMEERR ; 
 int /*<<< orphan*/  CUE_TX_EXCESSCOLL ; 
 int /*<<< orphan*/  CUE_TX_MULTICOLL ; 
 int /*<<< orphan*/  CUE_TX_SINGLECOLL ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int cue_csr_read_2 (struct cue_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct cue_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
cue_tick(struct usb_ether *ue)
{
	struct cue_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	CUE_LOCK_ASSERT(sc, MA_OWNED);

	if_inc_counter(ifp, IFCOUNTER_COLLISIONS, cue_csr_read_2(sc, CUE_TX_SINGLECOLL));
	if_inc_counter(ifp, IFCOUNTER_COLLISIONS, cue_csr_read_2(sc, CUE_TX_MULTICOLL));
	if_inc_counter(ifp, IFCOUNTER_COLLISIONS, cue_csr_read_2(sc, CUE_TX_EXCESSCOLL));

	if (cue_csr_read_2(sc, CUE_RX_FRAMEERR))
		if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
}