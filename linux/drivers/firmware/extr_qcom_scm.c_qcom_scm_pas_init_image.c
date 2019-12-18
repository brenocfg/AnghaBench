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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __qcom_scm_pas_init_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* __scm ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  qcom_scm_clk_disable () ; 
 int qcom_scm_clk_enable () ; 

int qcom_scm_pas_init_image(u32 peripheral, const void *metadata, size_t size)
{
	dma_addr_t mdata_phys;
	void *mdata_buf;
	int ret;

	/*
	 * During the scm call memory protection will be enabled for the meta
	 * data blob, so make sure it's physically contiguous, 4K aligned and
	 * non-cachable to avoid XPU violations.
	 */
	mdata_buf = dma_alloc_coherent(__scm->dev, size, &mdata_phys,
				       GFP_KERNEL);
	if (!mdata_buf) {
		dev_err(__scm->dev, "Allocation of metadata buffer failed.\n");
		return -ENOMEM;
	}
	memcpy(mdata_buf, metadata, size);

	ret = qcom_scm_clk_enable();
	if (ret)
		goto free_metadata;

	ret = __qcom_scm_pas_init_image(__scm->dev, peripheral, mdata_phys);

	qcom_scm_clk_disable();

free_metadata:
	dma_free_coherent(__scm->dev, size, mdata_buf, mdata_phys);

	return ret;
}