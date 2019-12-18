#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdhci_xenon_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/ * reg_vqmmc; } ;
struct TYPE_3__ {int vccq; } ;
struct TYPE_4__ {TYPE_1__ ios; } ;
struct sdhci_slot {TYPE_2__ host; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct sdhci_slot* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct sdhci_xenon_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int regulator_set_voltage (int /*<<< orphan*/ *,int,int) ; 
#define  vccq_180 129 
#define  vccq_330 128 

__attribute__((used)) static int
sdhci_xenon_switch_vccq(device_t brdev, device_t reqdev)
{
	struct sdhci_xenon_softc *sc;
	struct sdhci_slot *slot;
	int uvolt, err;

	sc = device_get_softc(brdev);

        if (sc->reg_vqmmc == NULL)
		return EOPNOTSUPP;

	slot = device_get_ivars(reqdev);
	switch (slot->host.ios.vccq) {
	case vccq_180:
		uvolt = 1800000;
		break;
	case vccq_330:
		uvolt = 3300000;
		break;
	default:
		return EINVAL;
	}

	err = regulator_set_voltage(sc->reg_vqmmc, uvolt, uvolt);
	if (err != 0) {
		device_printf(sc->dev,
		    "Cannot set vqmmc to %d<->%d\n",
		    uvolt,
		    uvolt);
		return (err);
	}

	return (0);
}