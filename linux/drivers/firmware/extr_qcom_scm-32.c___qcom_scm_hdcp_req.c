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
struct qcom_scm_hdcp_req {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  QCOM_SCM_CMD_HDCP ; 
 int QCOM_SCM_HDCP_MAX_REQ_CNT ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_HDCP ; 
 int qcom_scm_call (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qcom_scm_hdcp_req*,int,int*,int) ; 

int __qcom_scm_hdcp_req(struct device *dev, struct qcom_scm_hdcp_req *req,
			u32 req_cnt, u32 *resp)
{
	if (req_cnt > QCOM_SCM_HDCP_MAX_REQ_CNT)
		return -ERANGE;

	return qcom_scm_call(dev, QCOM_SCM_SVC_HDCP, QCOM_SCM_CMD_HDCP,
		req, req_cnt * sizeof(*req), resp, sizeof(*resp));
}