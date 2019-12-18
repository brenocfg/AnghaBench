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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_TRANSITION_NOTIFIER ; 
 int /*<<< orphan*/  OSIRIS_GPIO_DVS ; 
 int cpufreq_register_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  osiris_dvs_nb ; 
 int /*<<< orphan*/  osiris_dvs_tps_setdvs (int) ; 

__attribute__((used)) static int osiris_dvs_probe(struct platform_device *pdev)
{
	int ret;

	dev_info(&pdev->dev, "initialising\n");

	ret = gpio_request(OSIRIS_GPIO_DVS, "osiris-dvs");
	if (ret) {
		dev_err(&pdev->dev, "cannot claim gpio\n");
		goto err_nogpio;
	}

	/* start with dvs disabled */
	gpio_direction_output(OSIRIS_GPIO_DVS, 1);

	ret = cpufreq_register_notifier(&osiris_dvs_nb,
					CPUFREQ_TRANSITION_NOTIFIER);
	if (ret) {
		dev_err(&pdev->dev, "failed to register with cpufreq\n");
		goto err_nofreq;
	}

	osiris_dvs_tps_setdvs(true);

	return 0;

err_nofreq:
	gpio_free(OSIRIS_GPIO_DVS);

err_nogpio:
	return ret;
}