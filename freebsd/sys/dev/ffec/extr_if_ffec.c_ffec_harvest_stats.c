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
struct ffec_softc {struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_IEEE_R_DROP ; 
 int /*<<< orphan*/  FEC_IEEE_R_MACERR ; 
 int /*<<< orphan*/  FEC_RMON_R_CRC_ALIGN ; 
 int /*<<< orphan*/  FEC_RMON_R_FRAG ; 
 int /*<<< orphan*/  FEC_RMON_R_JAB ; 
 int /*<<< orphan*/  FEC_RMON_R_MC_PKT ; 
 int /*<<< orphan*/  FEC_RMON_R_OVERSIZE ; 
 int /*<<< orphan*/  FEC_RMON_R_PACKETS ; 
 int /*<<< orphan*/  FEC_RMON_R_UNDERSIZE ; 
 int /*<<< orphan*/  FEC_RMON_T_COL ; 
 int /*<<< orphan*/  FEC_RMON_T_CRC_ALIGN ; 
 int /*<<< orphan*/  FEC_RMON_T_FRAG ; 
 int /*<<< orphan*/  FEC_RMON_T_JAB ; 
 int /*<<< orphan*/  FEC_RMON_T_MC_PKT ; 
 int /*<<< orphan*/  FEC_RMON_T_OVERSIZE ; 
 int /*<<< orphan*/  FEC_RMON_T_PACKETS ; 
 int /*<<< orphan*/  FEC_RMON_T_UNDERSIZE ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 scalar_t__ RD4 (struct ffec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffec_clear_stats (struct ffec_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ffec_harvest_stats(struct ffec_softc *sc)
{
	struct ifnet *ifp;

	ifp = sc->ifp;

	/*
	 * - FEC_IEEE_R_DROP is "dropped due to invalid start frame delimiter"
	 *   so it's really just another type of input error.
	 * - FEC_IEEE_R_MACERR is "no receive fifo space"; count as input drops.
	 */
	if_inc_counter(ifp, IFCOUNTER_IPACKETS, RD4(sc, FEC_RMON_R_PACKETS));
	if_inc_counter(ifp, IFCOUNTER_IMCASTS, RD4(sc, FEC_RMON_R_MC_PKT));
	if_inc_counter(ifp, IFCOUNTER_IERRORS,
	    RD4(sc, FEC_RMON_R_CRC_ALIGN) + RD4(sc, FEC_RMON_R_UNDERSIZE) +
	    RD4(sc, FEC_RMON_R_OVERSIZE) + RD4(sc, FEC_RMON_R_FRAG) +
	    RD4(sc, FEC_RMON_R_JAB) + RD4(sc, FEC_IEEE_R_DROP));

	if_inc_counter(ifp, IFCOUNTER_IQDROPS, RD4(sc, FEC_IEEE_R_MACERR));

	if_inc_counter(ifp, IFCOUNTER_OPACKETS, RD4(sc, FEC_RMON_T_PACKETS));
	if_inc_counter(ifp, IFCOUNTER_OMCASTS, RD4(sc, FEC_RMON_T_MC_PKT));
	if_inc_counter(ifp, IFCOUNTER_OERRORS,
	    RD4(sc, FEC_RMON_T_CRC_ALIGN) + RD4(sc, FEC_RMON_T_UNDERSIZE) +
	    RD4(sc, FEC_RMON_T_OVERSIZE) + RD4(sc, FEC_RMON_T_FRAG) +
	    RD4(sc, FEC_RMON_T_JAB));

	if_inc_counter(ifp, IFCOUNTER_COLLISIONS, RD4(sc, FEC_RMON_T_COL));

	ffec_clear_stats(sc);
}