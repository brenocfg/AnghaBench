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
struct nitrox_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int nitrox_bist_check (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_aqm_unit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_bmi_unit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_bmo_unit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_efl_unit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_emu_unit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_lbc_unit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_nps_core_unit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_nps_pkt_unit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_pom_unit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_rand_unit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_get_hwinfo (struct nitrox_device*) ; 
 int nitrox_load_fw (struct nitrox_device*) ; 

__attribute__((used)) static int nitrox_pf_hw_init(struct nitrox_device *ndev)
{
	int err;

	err = nitrox_bist_check(ndev);
	if (err) {
		dev_err(&ndev->pdev->dev, "BIST check failed\n");
		return err;
	}
	/* get cores information */
	nitrox_get_hwinfo(ndev);

	nitrox_config_nps_core_unit(ndev);
	nitrox_config_aqm_unit(ndev);
	nitrox_config_nps_pkt_unit(ndev);
	nitrox_config_pom_unit(ndev);
	nitrox_config_efl_unit(ndev);
	/* configure IO units */
	nitrox_config_bmi_unit(ndev);
	nitrox_config_bmo_unit(ndev);
	/* configure Local Buffer Cache */
	nitrox_config_lbc_unit(ndev);
	nitrox_config_rand_unit(ndev);

	/* load firmware on cores */
	err = nitrox_load_fw(ndev);
	if (err)
		return err;

	nitrox_config_emu_unit(ndev);

	return 0;
}