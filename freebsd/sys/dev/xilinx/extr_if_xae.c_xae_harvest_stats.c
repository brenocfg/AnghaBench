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
struct xae_softc {struct ifnet* ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_OBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  RX_ALIGNMENT_ERRORS ; 
 int /*<<< orphan*/  RX_FRAME_CHECK_SEQ_ERROR ; 
 int /*<<< orphan*/  RX_GOOD_FRAMES ; 
 int /*<<< orphan*/  RX_GOOD_MCASTS ; 
 int /*<<< orphan*/  RX_LEN_OUT_OF_RANGE ; 
 int /*<<< orphan*/  TX_BYTES ; 
 int /*<<< orphan*/  TX_EXCESS_COLLISIONS ; 
 int /*<<< orphan*/  TX_GOOD_FRAMES ; 
 int /*<<< orphan*/  TX_GOOD_MCASTS ; 
 int /*<<< orphan*/  TX_GOOD_UNDERRUN_ERRORS ; 
 int /*<<< orphan*/  TX_LATE_COLLISIONS ; 
 int /*<<< orphan*/  TX_MULTI_COLLISION_FRAMES ; 
 int /*<<< orphan*/  TX_SINGLE_COLLISION_FRAMES ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ xae_stat (struct xae_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xae_harvest_stats(struct xae_softc *sc)
{
	struct ifnet *ifp;

	ifp = sc->ifp;

	if_inc_counter(ifp, IFCOUNTER_IPACKETS, xae_stat(sc, RX_GOOD_FRAMES));
	if_inc_counter(ifp, IFCOUNTER_IMCASTS, xae_stat(sc, RX_GOOD_MCASTS));
	if_inc_counter(ifp, IFCOUNTER_IERRORS,
	    xae_stat(sc, RX_FRAME_CHECK_SEQ_ERROR) +
	    xae_stat(sc, RX_LEN_OUT_OF_RANGE) +
	    xae_stat(sc, RX_ALIGNMENT_ERRORS));

	if_inc_counter(ifp, IFCOUNTER_OBYTES, xae_stat(sc, TX_BYTES));
	if_inc_counter(ifp, IFCOUNTER_OPACKETS, xae_stat(sc, TX_GOOD_FRAMES));
	if_inc_counter(ifp, IFCOUNTER_OMCASTS, xae_stat(sc, TX_GOOD_MCASTS));
	if_inc_counter(ifp, IFCOUNTER_OERRORS,
	    xae_stat(sc, TX_GOOD_UNDERRUN_ERRORS));

	if_inc_counter(ifp, IFCOUNTER_COLLISIONS,
	    xae_stat(sc, TX_SINGLE_COLLISION_FRAMES) +
	    xae_stat(sc, TX_MULTI_COLLISION_FRAMES) +
	    xae_stat(sc, TX_LATE_COLLISIONS) +
	    xae_stat(sc, TX_EXCESS_COLLISIONS));
}