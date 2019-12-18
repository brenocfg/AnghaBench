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
struct scatterlist {int /*<<< orphan*/  length; } ;
struct s5p_aes_dev {struct scatterlist* sg_src; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_set_indata(struct s5p_aes_dev *dev, struct scatterlist *sg)
{
	if (!sg->length)
		return -EINVAL;

	if (!dma_map_sg(dev->dev, sg, 1, DMA_TO_DEVICE))
		return -ENOMEM;

	dev->sg_src = sg;

	return 0;
}