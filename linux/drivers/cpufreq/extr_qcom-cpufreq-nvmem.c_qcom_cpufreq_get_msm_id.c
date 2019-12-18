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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum _msm_id { ____Placeholder__msm_id } _msm_id ;
typedef  enum _msm8996_version { ____Placeholder__msm8996_version } _msm8996_version ;

/* Variables and functions */
#define  APQ8096SG 131 
#define  APQ8096V3 130 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
#define  MSM8996SG 129 
#define  MSM8996V3 128 
 int MSM8996_SG ; 
 int MSM8996_V3 ; 
 int /*<<< orphan*/  MSM_ID_SMEM ; 
 int NUM_OF_MSM8996_VERSIONS ; 
 int /*<<< orphan*/  QCOM_SMEM_HOST_ANY ; 
 int /*<<< orphan*/ * qcom_smem_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static enum _msm8996_version qcom_cpufreq_get_msm_id(void)
{
	size_t len;
	u32 *msm_id;
	enum _msm8996_version version;

	msm_id = qcom_smem_get(QCOM_SMEM_HOST_ANY, MSM_ID_SMEM, &len);
	if (IS_ERR(msm_id))
		return NUM_OF_MSM8996_VERSIONS;

	/* The first 4 bytes are format, next to them is the actual msm-id */
	msm_id++;

	switch ((enum _msm_id)*msm_id) {
	case MSM8996V3:
	case APQ8096V3:
		version = MSM8996_V3;
		break;
	case MSM8996SG:
	case APQ8096SG:
		version = MSM8996_SG;
		break;
	default:
		version = NUM_OF_MSM8996_VERSIONS;
	}

	return version;
}