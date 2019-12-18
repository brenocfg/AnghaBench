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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* mtkswitch_write ) (struct mtkswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* mtkswitch_read ) (struct mtkswitch_softc*,int /*<<< orphan*/ ) ;} ;
struct mtkswitch_softc {TYPE_1__ hal; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTKSWITCH_HI16_MSK ; 
 scalar_t__ MTKSWITCH_IS_HI16 (int) ; 
 int /*<<< orphan*/  MTKSWITCH_LO16_MSK ; 
 int /*<<< orphan*/  MTKSWITCH_REG32 (int) ; 
 int /*<<< orphan*/  MTKSWITCH_TO_HI16 (int) ; 
 int /*<<< orphan*/  MTKSWITCH_TO_LO16 (int) ; 
 struct mtkswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mtkswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtkswitch_reg_write(device_t dev, int reg, int val)
{
	struct mtkswitch_softc *sc = device_get_softc(dev);
	uint32_t tmp;

	tmp = sc->hal.mtkswitch_read(sc, MTKSWITCH_REG32(reg));
	if (MTKSWITCH_IS_HI16(reg)) {
		tmp &= MTKSWITCH_LO16_MSK;
		tmp |= MTKSWITCH_TO_HI16(val);
	} else {
		tmp &= MTKSWITCH_HI16_MSK;
		tmp |= MTKSWITCH_TO_LO16(val);
	}
	sc->hal.mtkswitch_write(sc, MTKSWITCH_REG32(reg), tmp);

	return (0);
}