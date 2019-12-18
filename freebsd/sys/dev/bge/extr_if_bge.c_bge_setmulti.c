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
typedef  int uint32_t ;
struct bge_softc {int /*<<< orphan*/  bge_ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_LOCK_ASSERT (struct bge_softc*) ; 
 scalar_t__ BGE_MAR0 ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bge_softc*,scalar_t__,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  bge_hash_maddr ; 
 int /*<<< orphan*/  if_foreach_llmaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bge_setmulti(struct bge_softc *sc)
{
	if_t ifp;
	uint32_t hashes[4] = { 0, 0, 0, 0 };
	int i;

	BGE_LOCK_ASSERT(sc);

	ifp = sc->bge_ifp;

	if (if_getflags(ifp) & IFF_ALLMULTI || if_getflags(ifp) & IFF_PROMISC) {
		for (i = 0; i < 4; i++)
			CSR_WRITE_4(sc, BGE_MAR0 + (i * 4), 0xFFFFFFFF);
		return;
	}

	/* First, zot all the existing filters. */
	for (i = 0; i < 4; i++)
		CSR_WRITE_4(sc, BGE_MAR0 + (i * 4), 0);

	if_foreach_llmaddr(ifp, bge_hash_maddr, hashes);

	for (i = 0; i < 4; i++)
		CSR_WRITE_4(sc, BGE_MAR0 + (i * 4), hashes[i]);
}