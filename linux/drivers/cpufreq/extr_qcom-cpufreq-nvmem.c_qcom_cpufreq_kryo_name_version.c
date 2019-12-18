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
typedef  scalar_t__ u8 ;
struct qcom_cpufreq_drv {int versions; } ;
struct nvmem_cell {int dummy; } ;
struct device {int dummy; } ;
typedef  enum _msm8996_version { ____Placeholder__msm8996_version } _msm8996_version ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (scalar_t__*) ; 
#define  MSM8996_SG 129 
#define  MSM8996_V3 128 
 int NUM_OF_MSM8996_VERSIONS ; 
 int PTR_ERR (scalar_t__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* nvmem_cell_read (struct nvmem_cell*,size_t*) ; 
 int qcom_cpufreq_get_msm_id () ; 

__attribute__((used)) static int qcom_cpufreq_kryo_name_version(struct device *cpu_dev,
					  struct nvmem_cell *speedbin_nvmem,
					  struct qcom_cpufreq_drv *drv)
{
	size_t len;
	u8 *speedbin;
	enum _msm8996_version msm8996_version;

	msm8996_version = qcom_cpufreq_get_msm_id();
	if (NUM_OF_MSM8996_VERSIONS == msm8996_version) {
		dev_err(cpu_dev, "Not Snapdragon 820/821!");
		return -ENODEV;
	}

	speedbin = nvmem_cell_read(speedbin_nvmem, &len);
	if (IS_ERR(speedbin))
		return PTR_ERR(speedbin);

	switch (msm8996_version) {
	case MSM8996_V3:
		drv->versions = 1 << (unsigned int)(*speedbin);
		break;
	case MSM8996_SG:
		drv->versions = 1 << ((unsigned int)(*speedbin) + 4);
		break;
	default:
		BUG();
		break;
	}

	kfree(speedbin);
	return 0;
}