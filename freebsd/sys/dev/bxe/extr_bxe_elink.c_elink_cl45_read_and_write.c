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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct elink_phy {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void elink_cl45_read_and_write(struct bxe_softc *sc,
				      struct elink_phy *phy,
				      uint8_t devad, uint16_t reg, uint16_t and_val)
{
	uint16_t val;
	elink_cl45_read(sc, phy, devad, reg, &val);
	elink_cl45_write(sc, phy, devad, reg, val & and_val);
}