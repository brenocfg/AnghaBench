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
struct TYPE_2__ {int (* mtkswitch_reg_read ) (int /*<<< orphan*/ ,int) ;} ;
struct mtkswitch_softc {TYPE_1__ hal; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct mtkswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mtkswitch_readreg(device_t dev, int addr)
{
	struct mtkswitch_softc *sc = device_get_softc(dev);

	return (sc->hal.mtkswitch_reg_read(dev, addr));
}