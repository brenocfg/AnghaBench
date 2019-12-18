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
struct TYPE_2__ {int /*<<< orphan*/  pol; int /*<<< orphan*/  pin; int /*<<< orphan*/ * dev; } ;
struct aml8726_mmc_softc {TYPE_1__ pwr_en; } ;

/* Variables and functions */
 int GPIO_PIN_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWR_OFF_FLAG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_mmc_power_off(struct aml8726_mmc_softc *sc)
{

	if (sc->pwr_en.dev == NULL)
		return (0);

	return (GPIO_PIN_SET(sc->pwr_en.dev, sc->pwr_en.pin,
	    PWR_OFF_FLAG(sc->pwr_en.pol)));
}