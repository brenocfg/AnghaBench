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
struct ifnet {int dummy; } ;
struct dwc_softc {scalar_t__ stats_harvest_count; struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 scalar_t__ READ4 (struct dwc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXALIGNMENTERROR ; 
 int /*<<< orphan*/  RXCRCERROR ; 
 int /*<<< orphan*/  RXFRAMECOUNT_GB ; 
 int /*<<< orphan*/  RXJABBERERROR ; 
 int /*<<< orphan*/  RXLENGTHERROR ; 
 int /*<<< orphan*/  RXMULTICASTFRAMES_G ; 
 int /*<<< orphan*/  RXOVERSIZE_G ; 
 int /*<<< orphan*/  RXRUNTERROR ; 
 int /*<<< orphan*/  RXUNDERSIZE_G ; 
 scalar_t__ STATS_HARVEST_INTERVAL ; 
 int /*<<< orphan*/  TXCARRIERERR ; 
 int /*<<< orphan*/  TXEXCESSDEF ; 
 int /*<<< orphan*/  TXEXESSCOL ; 
 int /*<<< orphan*/  TXFRAMECOUNT_G ; 
 int /*<<< orphan*/  TXLATECOL ; 
 int /*<<< orphan*/  TXMULTICASTFRAMES_G ; 
 int /*<<< orphan*/  TXOVERSIZE_G ; 
 int /*<<< orphan*/  TXUNDERFLOWERROR ; 
 int /*<<< orphan*/  dwc_clear_stats (struct dwc_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
dwc_harvest_stats(struct dwc_softc *sc)
{
	struct ifnet *ifp;

	/* We don't need to harvest too often. */
	if (++sc->stats_harvest_count < STATS_HARVEST_INTERVAL)
		return;

	sc->stats_harvest_count = 0;
	ifp = sc->ifp;

	if_inc_counter(ifp, IFCOUNTER_IPACKETS, READ4(sc, RXFRAMECOUNT_GB));
	if_inc_counter(ifp, IFCOUNTER_IMCASTS, READ4(sc, RXMULTICASTFRAMES_G));
	if_inc_counter(ifp, IFCOUNTER_IERRORS,
	    READ4(sc, RXOVERSIZE_G) + READ4(sc, RXUNDERSIZE_G) +
	    READ4(sc, RXCRCERROR) + READ4(sc, RXALIGNMENTERROR) +
	    READ4(sc, RXRUNTERROR) + READ4(sc, RXJABBERERROR) +
	    READ4(sc, RXLENGTHERROR));

	if_inc_counter(ifp, IFCOUNTER_OPACKETS, READ4(sc, TXFRAMECOUNT_G));
	if_inc_counter(ifp, IFCOUNTER_OMCASTS, READ4(sc, TXMULTICASTFRAMES_G));
	if_inc_counter(ifp, IFCOUNTER_OERRORS,
	    READ4(sc, TXOVERSIZE_G) + READ4(sc, TXEXCESSDEF) +
	    READ4(sc, TXCARRIERERR) + READ4(sc, TXUNDERFLOWERROR));

	if_inc_counter(ifp, IFCOUNTER_COLLISIONS,
	    READ4(sc, TXEXESSCOL) + READ4(sc, TXLATECOL));

	dwc_clear_stats(sc);
}