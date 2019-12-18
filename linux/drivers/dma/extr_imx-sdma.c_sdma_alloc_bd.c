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
typedef  int u32 ;
struct sdma_desc {int num_bd; int /*<<< orphan*/  bd; int /*<<< orphan*/  bd_phys; TYPE_2__* sdmac; } ;
struct sdma_buffer_descriptor {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sdma; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdma_alloc_bd(struct sdma_desc *desc)
{
	u32 bd_size = desc->num_bd * sizeof(struct sdma_buffer_descriptor);
	int ret = 0;

	desc->bd = dma_alloc_coherent(desc->sdmac->sdma->dev, bd_size,
				       &desc->bd_phys, GFP_NOWAIT);
	if (!desc->bd) {
		ret = -ENOMEM;
		goto out;
	}
out:
	return ret;
}