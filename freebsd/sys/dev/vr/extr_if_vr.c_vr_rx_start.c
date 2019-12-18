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
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  vr_rx_cons; } ;
struct vr_softc {TYPE_1__ vr_cdata; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int CSR_READ_1 (struct vr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct vr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR_CR0 ; 
 int VR_CR0_RX_GO ; 
 int VR_CR0_RX_ON ; 
 int /*<<< orphan*/  VR_RXADDR ; 
 int /*<<< orphan*/  VR_RX_RING_ADDR (struct vr_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vr_rx_start(struct vr_softc *sc)
{
	bus_addr_t	addr;
	uint8_t		cmd;

	cmd = CSR_READ_1(sc, VR_CR0);
	if ((cmd & VR_CR0_RX_ON) == 0) {
		addr = VR_RX_RING_ADDR(sc, sc->vr_cdata.vr_rx_cons);
		CSR_WRITE_4(sc, VR_RXADDR, VR_ADDR_LO(addr));
		cmd |= VR_CR0_RX_ON;
		CSR_WRITE_1(sc, VR_CR0, cmd);
	}
	CSR_WRITE_1(sc, VR_CR0, cmd | VR_CR0_RX_GO);
}