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
struct of_phandle_args {int /*<<< orphan*/ * args; } ;
struct of_dma {int /*<<< orphan*/  of_dma_data; } ;
struct dma_chan {int dummy; } ;
struct coh901318_filter_args {int /*<<< orphan*/  ch_nr; int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE ; 
 int /*<<< orphan*/  coh901318_filter_base_and_id ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 struct dma_chan* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct coh901318_filter_args*) ; 

__attribute__((used)) static struct dma_chan *coh901318_xlate(struct of_phandle_args *dma_spec,
					struct of_dma *ofdma)
{
	struct coh901318_filter_args args = {
		.base = ofdma->of_dma_data,
		.ch_nr = dma_spec->args[0],
	};
	dma_cap_mask_t cap;
	dma_cap_zero(cap);
	dma_cap_set(DMA_SLAVE, cap);

	return dma_request_channel(cap, coh901318_filter_base_and_id, &args);
}