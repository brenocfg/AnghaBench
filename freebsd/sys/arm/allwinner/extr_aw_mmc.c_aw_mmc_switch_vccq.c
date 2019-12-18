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
struct TYPE_3__ {int vccq; } ;
struct TYPE_4__ {TYPE_1__ ios; } ;
struct aw_mmc_softc {int /*<<< orphan*/  aw_dev; int /*<<< orphan*/ * aw_reg_vqmmc; TYPE_2__ aw_host; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct aw_mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int regulator_set_voltage (int /*<<< orphan*/ *,int,int) ; 
#define  vccq_180 129 
#define  vccq_330 128 

__attribute__((used)) static int
aw_mmc_switch_vccq(device_t bus, device_t child)
{
	struct aw_mmc_softc *sc;
	int uvolt, err;

	sc = device_get_softc(bus);

	if (sc->aw_reg_vqmmc == NULL)
		return EOPNOTSUPP;

	switch (sc->aw_host.ios.vccq) {
	case vccq_180:
		uvolt = 1800000;
		break;
	case vccq_330:
		uvolt = 3300000;
		break;
	default:
		return EINVAL;
	}

	err = regulator_set_voltage(sc->aw_reg_vqmmc, uvolt, uvolt);
	if (err != 0) {
		device_printf(sc->aw_dev,
		    "Cannot set vqmmc to %d<->%d\n",
		    uvolt,
		    uvolt);
		return (err);
	}

	return (0);
}