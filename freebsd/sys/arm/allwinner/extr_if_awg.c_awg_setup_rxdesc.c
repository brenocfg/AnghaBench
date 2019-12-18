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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {TYPE_2__* desc_ring; } ;
struct awg_softc {TYPE_1__ rx; } ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_4__ {void* status; void* size; void* addr; } ;

/* Variables and functions */
 scalar_t__ MCLBYTES ; 
 scalar_t__ RX_DESC_CTL ; 
 void* htole32 (scalar_t__) ; 

__attribute__((used)) static void
awg_setup_rxdesc(struct awg_softc *sc, int index, bus_addr_t paddr)
{
	uint32_t status, size;

	status = RX_DESC_CTL;
	size = MCLBYTES - 1;

	sc->rx.desc_ring[index].addr = htole32((uint32_t)paddr);
	sc->rx.desc_ring[index].size = htole32(size);
	sc->rx.desc_ring[index].status = htole32(status);
}