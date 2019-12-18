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
struct mgb_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_UPDATE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int) ; 
 int MGB_MAC_ADD_ENBL ; 
 int MGB_MAC_ASD_ENBL ; 
 int /*<<< orphan*/  MGB_MAC_CR ; 
 int MGB_MAC_ENBL ; 
 int /*<<< orphan*/  MGB_MAC_RX ; 
 int /*<<< orphan*/  MGB_MAC_TX ; 
 int MGB_STS_OK ; 

__attribute__((used)) static int
mgb_mac_init(struct mgb_softc *sc)
{

	/**
	 * enable automatic duplex detection and
	 * automatic speed detection
	 */
	CSR_UPDATE_REG(sc, MGB_MAC_CR, MGB_MAC_ADD_ENBL | MGB_MAC_ASD_ENBL);
	CSR_UPDATE_REG(sc, MGB_MAC_TX, MGB_MAC_ENBL);
	CSR_UPDATE_REG(sc, MGB_MAC_RX, MGB_MAC_ENBL);

	return MGB_STS_OK;
}