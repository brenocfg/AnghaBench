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
struct cas_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  CAS_BARRIER (struct cas_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CAS_MAC_RX_CONF ; 
 int CAS_MAC_RX_CONF_EN ; 
 int CAS_READ_4 (struct cas_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAS_WRITE_4 (struct cas_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 scalar_t__ cas_bitwait (struct cas_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
cas_disable_rx(struct cas_softc *sc)
{

	CAS_WRITE_4(sc, CAS_MAC_RX_CONF,
	    CAS_READ_4(sc, CAS_MAC_RX_CONF) & ~CAS_MAC_RX_CONF_EN);
	CAS_BARRIER(sc, CAS_MAC_RX_CONF, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	if (cas_bitwait(sc, CAS_MAC_RX_CONF, CAS_MAC_RX_CONF_EN, 0))
		return (1);
	if (bootverbose)
		device_printf(sc->sc_dev, "cannot disable RX MAC\n");
	return (0);
}