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
typedef  int /*<<< orphan*/  u64 ;
struct dfl_feature_platform_data {int dummy; } ;
struct dfl_afu_dma_region {int dummy; } ;

/* Variables and functions */
 struct dfl_afu_dma_region* afu_dma_region_find (struct dfl_feature_platform_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dfl_afu_dma_region *
afu_dma_region_find_iova(struct dfl_feature_platform_data *pdata, u64 iova)
{
	return afu_dma_region_find(pdata, iova, 0);
}