#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct crypto4xx_device {scalar_t__ scatter_buffer_pa; TYPE_2__* sdr; scalar_t__ sdr_pa; TYPE_1__* core_dev; void* scatter_buffer_va; } ;
struct ce_sd {int dummy; } ;
struct TYPE_4__ {scalar_t__ ptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PPC4XX_NUM_SD ; 
 int PPC4XX_SD_BUFFER_SIZE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static u32 crypto4xx_build_sdr(struct crypto4xx_device *dev)
{
	int i;

	/* alloc memory for scatter descriptor ring */
	dev->sdr = dma_alloc_coherent(dev->core_dev->device,
				      sizeof(struct ce_sd) * PPC4XX_NUM_SD,
				      &dev->sdr_pa, GFP_ATOMIC);
	if (!dev->sdr)
		return -ENOMEM;

	dev->scatter_buffer_va =
		dma_alloc_coherent(dev->core_dev->device,
			PPC4XX_SD_BUFFER_SIZE * PPC4XX_NUM_SD,
			&dev->scatter_buffer_pa, GFP_ATOMIC);
	if (!dev->scatter_buffer_va) {
		dma_free_coherent(dev->core_dev->device,
				  sizeof(struct ce_sd) * PPC4XX_NUM_SD,
				  dev->sdr, dev->sdr_pa);
		return -ENOMEM;
	}

	for (i = 0; i < PPC4XX_NUM_SD; i++) {
		dev->sdr[i].ptr = dev->scatter_buffer_pa +
				  PPC4XX_SD_BUFFER_SIZE * i;
	}

	return 0;
}