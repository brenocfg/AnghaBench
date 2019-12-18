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
typedef  int /*<<< orphan*/  uint16_t ;
struct bwi_softc {int dummy; } ;
struct bwi_mac {struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_PHY_CTRL ; 
 int /*<<< orphan*/  BWI_PHY_DATA ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bwi_phy_write(struct bwi_mac *mac, uint16_t ctrl, uint16_t data)
{
	struct bwi_softc *sc = mac->mac_sc;

	CSR_WRITE_2(sc, BWI_PHY_CTRL, ctrl);
	CSR_WRITE_2(sc, BWI_PHY_DATA, data);
}