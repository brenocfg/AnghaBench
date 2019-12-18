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
struct ste_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_1 (struct ste_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_READ_2 (struct ste_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STE_LOCK_ASSERT (struct ste_softc*) ; 
 int /*<<< orphan*/  STE_STAT_CARRIER_ERR ; 
 int /*<<< orphan*/  STE_STAT_LATE_COLLS ; 
 int /*<<< orphan*/  STE_STAT_MULTI_COLLS ; 
 int /*<<< orphan*/  STE_STAT_RX_BCAST ; 
 int /*<<< orphan*/  STE_STAT_RX_FRAMES ; 
 int /*<<< orphan*/  STE_STAT_RX_LOST ; 
 int /*<<< orphan*/  STE_STAT_RX_MCAST ; 
 int /*<<< orphan*/  STE_STAT_RX_OCTETS_HI ; 
 int /*<<< orphan*/  STE_STAT_RX_OCTETS_LO ; 
 int /*<<< orphan*/  STE_STAT_SINGLE_COLLS ; 
 int /*<<< orphan*/  STE_STAT_TX_ABORT ; 
 int /*<<< orphan*/  STE_STAT_TX_BCAST ; 
 int /*<<< orphan*/  STE_STAT_TX_DEFER ; 
 int /*<<< orphan*/  STE_STAT_TX_EXDEFER ; 
 int /*<<< orphan*/  STE_STAT_TX_FRAMES ; 
 int /*<<< orphan*/  STE_STAT_TX_MCAST ; 
 int /*<<< orphan*/  STE_STAT_TX_OCTETS_HI ; 
 int /*<<< orphan*/  STE_STAT_TX_OCTETS_LO ; 

__attribute__((used)) static void
ste_stats_clear(struct ste_softc *sc)
{

	STE_LOCK_ASSERT(sc);

	/* Rx stats. */
	CSR_READ_2(sc, STE_STAT_RX_OCTETS_LO);
	CSR_READ_2(sc, STE_STAT_RX_OCTETS_HI);
	CSR_READ_2(sc, STE_STAT_RX_FRAMES);
	CSR_READ_1(sc, STE_STAT_RX_BCAST);
	CSR_READ_1(sc, STE_STAT_RX_MCAST);
	CSR_READ_1(sc, STE_STAT_RX_LOST);
	/* Tx stats. */
	CSR_READ_2(sc, STE_STAT_TX_OCTETS_LO);
	CSR_READ_2(sc, STE_STAT_TX_OCTETS_HI);
	CSR_READ_2(sc, STE_STAT_TX_FRAMES);
	CSR_READ_1(sc, STE_STAT_TX_BCAST);
	CSR_READ_1(sc, STE_STAT_TX_MCAST);
	CSR_READ_1(sc, STE_STAT_CARRIER_ERR);
	CSR_READ_1(sc, STE_STAT_SINGLE_COLLS);
	CSR_READ_1(sc, STE_STAT_MULTI_COLLS);
	CSR_READ_1(sc, STE_STAT_LATE_COLLS);
	CSR_READ_1(sc, STE_STAT_TX_DEFER);
	CSR_READ_1(sc, STE_STAT_TX_EXDEFER);
	CSR_READ_1(sc, STE_STAT_TX_ABORT);
}