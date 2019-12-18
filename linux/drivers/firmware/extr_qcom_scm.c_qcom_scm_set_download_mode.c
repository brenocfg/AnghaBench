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
struct TYPE_2__ {int /*<<< orphan*/  dev; scalar_t__ dload_mode_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_SCM_SET_DLOAD_MODE ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_BOOT ; 
 int __qcom_scm_io_writel (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int __qcom_scm_is_call_available (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __qcom_scm_set_dload_mode (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* __scm ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void qcom_scm_set_download_mode(bool enable)
{
	bool avail;
	int ret = 0;

	avail = __qcom_scm_is_call_available(__scm->dev,
					     QCOM_SCM_SVC_BOOT,
					     QCOM_SCM_SET_DLOAD_MODE);
	if (avail) {
		ret = __qcom_scm_set_dload_mode(__scm->dev, enable);
	} else if (__scm->dload_mode_addr) {
		ret = __qcom_scm_io_writel(__scm->dev, __scm->dload_mode_addr,
					   enable ? QCOM_SCM_SET_DLOAD_MODE : 0);
	} else {
		dev_err(__scm->dev,
			"No available mechanism for setting download mode\n");
	}

	if (ret)
		dev_err(__scm->dev, "failed to set download mode: %d\n", ret);
}