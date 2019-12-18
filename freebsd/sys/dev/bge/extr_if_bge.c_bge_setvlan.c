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
struct bge_softc {int /*<<< orphan*/  bge_ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_CLRBIT (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGE_LOCK_ASSERT (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_RXMODE_RX_KEEP_VLAN_DIAG ; 
 int /*<<< orphan*/  BGE_RX_MODE ; 
 int /*<<< orphan*/  BGE_SETBIT (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bge_setvlan(struct bge_softc *sc)
{
	if_t ifp;

	BGE_LOCK_ASSERT(sc);

	ifp = sc->bge_ifp;

	/* Enable or disable VLAN tag stripping as needed. */
	if (if_getcapenable(ifp) & IFCAP_VLAN_HWTAGGING)
		BGE_CLRBIT(sc, BGE_RX_MODE, BGE_RXMODE_RX_KEEP_VLAN_DIAG);
	else
		BGE_SETBIT(sc, BGE_RX_MODE, BGE_RXMODE_RX_KEEP_VLAN_DIAG);
}