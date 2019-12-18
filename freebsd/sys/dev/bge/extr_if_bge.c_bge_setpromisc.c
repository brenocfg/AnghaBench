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
 int /*<<< orphan*/  BGE_RXMODE_RX_PROMISC ; 
 int /*<<< orphan*/  BGE_RX_MODE ; 
 int /*<<< orphan*/  BGE_SETBIT (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFF_PROMISC ; 
 int if_getflags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bge_setpromisc(struct bge_softc *sc)
{
	if_t ifp;

	BGE_LOCK_ASSERT(sc);

	ifp = sc->bge_ifp;

	/* Enable or disable promiscuous mode as needed. */
	if (if_getflags(ifp) & IFF_PROMISC)
		BGE_SETBIT(sc, BGE_RX_MODE, BGE_RXMODE_RX_PROMISC);
	else
		BGE_CLRBIT(sc, BGE_RX_MODE, BGE_RXMODE_RX_PROMISC);
}