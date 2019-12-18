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
typedef  int /*<<< orphan*/  uint32_t ;
struct rsu_softc {scalar_t__ sc_rx_checksum_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92S_RCR ; 
 int /*<<< orphan*/  R92S_RCR_AICV ; 
 int /*<<< orphan*/  R92S_RCR_APP_PHYSTS ; 
 int /*<<< orphan*/  R92S_RCR_TCP_OFFLD_EN ; 
 int /*<<< orphan*/  RSU_ASSERT_LOCKED (struct rsu_softc*) ; 
 int /*<<< orphan*/  rsu_read_4 (struct rsu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsu_rxfilter_refresh (struct rsu_softc*) ; 
 int /*<<< orphan*/  rsu_set_multi (struct rsu_softc*) ; 
 int /*<<< orphan*/  rsu_write_4 (struct rsu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rsu_rxfilter_init(struct rsu_softc *sc)
{
	uint32_t reg;

	RSU_ASSERT_LOCKED(sc);

	/* Setup multicast filter. */
	rsu_set_multi(sc);

	/* Adjust Rx filter. */
	reg = rsu_read_4(sc, R92S_RCR);
	reg &= ~R92S_RCR_AICV;
	reg |= R92S_RCR_APP_PHYSTS;
	if (sc->sc_rx_checksum_enable)
		reg |= R92S_RCR_TCP_OFFLD_EN;
	rsu_write_4(sc, R92S_RCR, reg);

	/* Update dynamic Rx filter parts. */
	rsu_rxfilter_refresh(sc);
}