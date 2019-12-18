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
struct scatterlist {int dummy; } ;
struct s5p_aes_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCBTDMAL ; 
 int /*<<< orphan*/  FCBTDMAS ; 
 int /*<<< orphan*/  SSS_WRITE (struct s5p_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist const*) ; 
 int /*<<< orphan*/  sg_dma_len (struct scatterlist const*) ; 

__attribute__((used)) static void s5p_set_dma_outdata(struct s5p_aes_dev *dev,
				const struct scatterlist *sg)
{
	SSS_WRITE(dev, FCBTDMAS, sg_dma_address(sg));
	SSS_WRITE(dev, FCBTDMAL, sg_dma_len(sg));
}