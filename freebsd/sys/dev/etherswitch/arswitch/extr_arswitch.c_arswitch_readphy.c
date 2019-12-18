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
struct TYPE_2__ {int (* arswitch_phy_read ) (int /*<<< orphan*/ ,int,int) ;} ;
struct arswitch_softc {TYPE_1__ hal; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct arswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
arswitch_readphy(device_t dev, int phy, int reg)
{
	struct arswitch_softc *sc = device_get_softc(dev);

	return (sc->hal.arswitch_phy_read(dev, phy, reg));
}