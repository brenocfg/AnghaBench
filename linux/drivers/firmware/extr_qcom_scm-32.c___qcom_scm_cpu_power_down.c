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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_SCM_CMD_TERMINATE_PC ; 
 int QCOM_SCM_FLUSH_FLAG_MASK ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_BOOT ; 
 int /*<<< orphan*/  qcom_scm_call_atomic1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void __qcom_scm_cpu_power_down(u32 flags)
{
	qcom_scm_call_atomic1(QCOM_SCM_SVC_BOOT, QCOM_SCM_CMD_TERMINATE_PC,
			flags & QCOM_SCM_FLUSH_FLAG_MASK);
}