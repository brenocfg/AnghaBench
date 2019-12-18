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
typedef  int uint16_t ;
struct elink_phy {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void elink_sfp_mask_fault(struct bxe_softc *sc,
				 struct elink_phy *phy,
				 uint16_t alarm_status_offset,
				 uint16_t alarm_ctrl_offset)
{
	uint16_t alarm_status, val;
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, alarm_status_offset,
			&alarm_status);
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, alarm_status_offset,
			&alarm_status);
	/* Mask or enable the fault event. */
	elink_cl45_read(sc, phy, MDIO_PMA_DEVAD, alarm_ctrl_offset, &val);
	if (alarm_status & (1<<0))
		val &= ~(1<<0);
	else
		val |= (1<<0);
	elink_cl45_write(sc, phy, MDIO_PMA_DEVAD, alarm_ctrl_offset, val);
}