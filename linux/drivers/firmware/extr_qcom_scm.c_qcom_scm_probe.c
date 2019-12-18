#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; } ;
struct qcom_scm {TYPE_1__* dev; int /*<<< orphan*/ * core_clk; TYPE_4__ reset; int /*<<< orphan*/ * bus_clk; int /*<<< orphan*/ * iface_clk; int /*<<< orphan*/  dload_mode_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 unsigned long SCM_HAS_BUS_CLK ; 
 unsigned long SCM_HAS_CORE_CLK ; 
 unsigned long SCM_HAS_IFACE_CLK ; 
 int /*<<< orphan*/  __qcom_scm_init () ; 
 struct qcom_scm* __scm ; 
 int clk_set_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 struct qcom_scm* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (TYPE_1__*,TYPE_4__*) ; 
 scalar_t__ download_mode ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 
 int qcom_scm_find_dload_address (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_scm_pas_reset_ops ; 
 int /*<<< orphan*/  qcom_scm_set_download_mode (int) ; 

__attribute__((used)) static int qcom_scm_probe(struct platform_device *pdev)
{
	struct qcom_scm *scm;
	unsigned long clks;
	int ret;

	scm = devm_kzalloc(&pdev->dev, sizeof(*scm), GFP_KERNEL);
	if (!scm)
		return -ENOMEM;

	ret = qcom_scm_find_dload_address(&pdev->dev, &scm->dload_mode_addr);
	if (ret < 0)
		return ret;

	clks = (unsigned long)of_device_get_match_data(&pdev->dev);

	scm->core_clk = devm_clk_get(&pdev->dev, "core");
	if (IS_ERR(scm->core_clk)) {
		if (PTR_ERR(scm->core_clk) == -EPROBE_DEFER)
			return PTR_ERR(scm->core_clk);

		if (clks & SCM_HAS_CORE_CLK) {
			dev_err(&pdev->dev, "failed to acquire core clk\n");
			return PTR_ERR(scm->core_clk);
		}

		scm->core_clk = NULL;
	}

	scm->iface_clk = devm_clk_get(&pdev->dev, "iface");
	if (IS_ERR(scm->iface_clk)) {
		if (PTR_ERR(scm->iface_clk) == -EPROBE_DEFER)
			return PTR_ERR(scm->iface_clk);

		if (clks & SCM_HAS_IFACE_CLK) {
			dev_err(&pdev->dev, "failed to acquire iface clk\n");
			return PTR_ERR(scm->iface_clk);
		}

		scm->iface_clk = NULL;
	}

	scm->bus_clk = devm_clk_get(&pdev->dev, "bus");
	if (IS_ERR(scm->bus_clk)) {
		if (PTR_ERR(scm->bus_clk) == -EPROBE_DEFER)
			return PTR_ERR(scm->bus_clk);

		if (clks & SCM_HAS_BUS_CLK) {
			dev_err(&pdev->dev, "failed to acquire bus clk\n");
			return PTR_ERR(scm->bus_clk);
		}

		scm->bus_clk = NULL;
	}

	scm->reset.ops = &qcom_scm_pas_reset_ops;
	scm->reset.nr_resets = 1;
	scm->reset.of_node = pdev->dev.of_node;
	ret = devm_reset_controller_register(&pdev->dev, &scm->reset);
	if (ret)
		return ret;

	/* vote for max clk rate for highest performance */
	ret = clk_set_rate(scm->core_clk, INT_MAX);
	if (ret)
		return ret;

	__scm = scm;
	__scm->dev = &pdev->dev;

	__qcom_scm_init();

	/*
	 * If requested enable "download mode", from this point on warmboot
	 * will cause the the boot stages to enter download mode, unless
	 * disabled below by a clean shutdown/reboot.
	 */
	if (download_mode)
		qcom_scm_set_download_mode(true);

	return 0;
}