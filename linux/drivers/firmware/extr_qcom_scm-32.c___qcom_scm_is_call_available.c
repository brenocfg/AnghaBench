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
typedef  int /*<<< orphan*/  svc_cmd ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ret_val ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_IS_CALL_AVAIL_CMD ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_INFO ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int qcom_scm_call (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

int __qcom_scm_is_call_available(struct device *dev, u32 svc_id, u32 cmd_id)
{
	int ret;
	__le32 svc_cmd = cpu_to_le32((svc_id << 10) | cmd_id);
	__le32 ret_val = 0;

	ret = qcom_scm_call(dev, QCOM_SCM_SVC_INFO, QCOM_IS_CALL_AVAIL_CMD,
			    &svc_cmd, sizeof(svc_cmd), &ret_val,
			    sizeof(ret_val));
	if (ret)
		return ret;

	return le32_to_cpu(ret_val);
}