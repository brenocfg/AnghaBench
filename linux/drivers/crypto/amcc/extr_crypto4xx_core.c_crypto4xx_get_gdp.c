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
struct crypto4xx_device {struct ce_gd* gdr; scalar_t__ gdr_pa; } ;
struct ce_gd {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static inline struct ce_gd *crypto4xx_get_gdp(struct crypto4xx_device *dev,
					      dma_addr_t *gd_dma, u32 idx)
{
	*gd_dma = dev->gdr_pa + sizeof(struct ce_gd) * idx;

	return &dev->gdr[idx];
}