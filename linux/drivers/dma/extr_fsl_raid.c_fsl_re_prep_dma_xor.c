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
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 struct dma_async_tx_descriptor* fsl_re_prep_dma_genq (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,size_t,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *fsl_re_prep_dma_xor(
		struct dma_chan *chan, dma_addr_t dest, dma_addr_t *src,
		unsigned int src_cnt, size_t len, unsigned long flags)
{
	/* NULL let genq take all coef as 1 */
	return fsl_re_prep_dma_genq(chan, dest, src, src_cnt, NULL, len, flags);
}