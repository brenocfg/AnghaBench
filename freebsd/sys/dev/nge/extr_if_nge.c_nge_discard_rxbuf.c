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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {struct nge_desc* nge_rx_ring; } ;
struct nge_softc {TYPE_1__ nge_rdata; } ;
struct nge_desc {scalar_t__ nge_extsts; int /*<<< orphan*/  nge_cmdsts; } ;

/* Variables and functions */
 scalar_t__ MCLBYTES ; 
 int /*<<< orphan*/  htole32 (scalar_t__) ; 

__attribute__((used)) static __inline void
nge_discard_rxbuf(struct nge_softc *sc, int idx)
{
	struct nge_desc *desc;

	desc = &sc->nge_rdata.nge_rx_ring[idx];
	desc->nge_cmdsts = htole32(MCLBYTES - sizeof(uint64_t));
	desc->nge_extsts = 0;
}