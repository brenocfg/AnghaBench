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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct microcode {scalar_t__ code_size; int core_mask; scalar_t__ phys_base; scalar_t__ is_ae; int /*<<< orphan*/  code; } ;
struct device {int dummy; } ;
struct cpt_device {int /*<<< orphan*/  reg_base; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_PF_ENGX_UCODE_BASE (int /*<<< orphan*/ ,int) ; 
 int CPT_MAX_SE_CORES ; 
 int CPT_MAX_TOTAL_CORES ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpt_write_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int cpt_load_microcode(struct cpt_device *cpt, struct microcode *mcode)
{
	int ret = 0, core = 0, shift = 0;
	u32 total_cores = 0;
	struct device *dev = &cpt->pdev->dev;

	if (!mcode || !mcode->code) {
		dev_err(dev, "Either the mcode is null or data is NULL\n");
		return -EINVAL;
	}

	if (mcode->code_size == 0) {
		dev_err(dev, "microcode size is 0\n");
		return -EINVAL;
	}

	/* Assumes 0-9 are SE cores for UCODE_BASE registers and
	 * AE core bases follow
	 */
	if (mcode->is_ae) {
		core = CPT_MAX_SE_CORES; /* start couting from 10 */
		total_cores = CPT_MAX_TOTAL_CORES; /* upto 15 */
	} else {
		core = 0; /* start couting from 0 */
		total_cores = CPT_MAX_SE_CORES; /* upto 9 */
	}

	/* Point to microcode for each core of the group */
	for (; core < total_cores ; core++, shift++) {
		if (mcode->core_mask & (1 << shift)) {
			cpt_write_csr64(cpt->reg_base,
					CPTX_PF_ENGX_UCODE_BASE(0, core),
					(u64)mcode->phys_base);
		}
	}
	return ret;
}