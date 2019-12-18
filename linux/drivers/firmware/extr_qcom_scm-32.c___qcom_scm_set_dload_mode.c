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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_SCM_SET_DLOAD_MODE ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_BOOT ; 
 int qcom_scm_call_atomic2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __qcom_scm_set_dload_mode(struct device *dev, bool enable)
{
	return qcom_scm_call_atomic2(QCOM_SCM_SVC_BOOT, QCOM_SCM_SET_DLOAD_MODE,
				     enable ? QCOM_SCM_SET_DLOAD_MODE : 0, 0);
}