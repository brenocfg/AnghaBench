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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXE_PHY_UNLOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_MDIO ; 
 int /*<<< orphan*/  bxe_release_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bxe_release_phy_lock(struct bxe_softc *sc)
{
	bxe_release_hw_lock(sc,HW_LOCK_RESOURCE_MDIO); 
	BXE_PHY_UNLOCK(sc);
}