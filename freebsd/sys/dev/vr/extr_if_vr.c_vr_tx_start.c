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
struct TYPE_2__ {scalar_t__ vr_tx_cnt; int /*<<< orphan*/  vr_tx_cons; } ;
struct vr_softc {int vr_watchdog_timer; TYPE_1__ vr_cdata; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int CSR_READ_1 (struct vr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct vr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR_CR0 ; 
 int /*<<< orphan*/  VR_CR0_TX_GO ; 
 int VR_CR0_TX_ON ; 
 int /*<<< orphan*/  VR_SETBIT (struct vr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR_TXADDR ; 
 int /*<<< orphan*/  VR_TX_RING_ADDR (struct vr_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vr_tx_start(struct vr_softc *sc)
{
	bus_addr_t	addr;
	uint8_t		cmd;

	cmd = CSR_READ_1(sc, VR_CR0);
	if ((cmd & VR_CR0_TX_ON) == 0) {
		addr = VR_TX_RING_ADDR(sc, sc->vr_cdata.vr_tx_cons);
		CSR_WRITE_4(sc, VR_TXADDR, VR_ADDR_LO(addr));
		cmd |= VR_CR0_TX_ON;
		CSR_WRITE_1(sc, VR_CR0, cmd);
	}
	if (sc->vr_cdata.vr_tx_cnt != 0) {
		sc->vr_watchdog_timer = 5;
		VR_SETBIT(sc, VR_CR0, VR_CR0_TX_GO);
	}
}