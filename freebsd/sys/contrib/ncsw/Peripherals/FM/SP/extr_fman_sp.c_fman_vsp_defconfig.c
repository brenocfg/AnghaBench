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
struct fm_storage_profile_params {int /*<<< orphan*/  no_scather_gather; int /*<<< orphan*/  dma_write_optimize; int /*<<< orphan*/  scatter_gather_cache_attr; int /*<<< orphan*/  header_cache_attr; int /*<<< orphan*/  int_context_cache_attr; int /*<<< orphan*/  dma_swap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FMAN_SP_DMA_HEADER_CACHE_ATTR ; 
 int /*<<< orphan*/  DEFAULT_FMAN_SP_DMA_INT_CONTEXT_CACHE_ATTR ; 
 int /*<<< orphan*/  DEFAULT_FMAN_SP_DMA_SCATTER_GATHER_CACHE_ATTR ; 
 int /*<<< orphan*/  DEFAULT_FMAN_SP_DMA_SWAP_DATA ; 
 int /*<<< orphan*/  DEFAULT_FMAN_SP_DMA_WRITE_OPTIMIZE ; 
 int /*<<< orphan*/  DEFAULT_FMAN_SP_NO_SCATTER_GATHER ; 

void fman_vsp_defconfig(struct fm_storage_profile_params *cfg)
{
    cfg->dma_swap_data =
            DEFAULT_FMAN_SP_DMA_SWAP_DATA;
    cfg->int_context_cache_attr =
            DEFAULT_FMAN_SP_DMA_INT_CONTEXT_CACHE_ATTR;
    cfg->header_cache_attr =
            DEFAULT_FMAN_SP_DMA_HEADER_CACHE_ATTR;
    cfg->scatter_gather_cache_attr =
            DEFAULT_FMAN_SP_DMA_SCATTER_GATHER_CACHE_ATTR;
    cfg->dma_write_optimize =
            DEFAULT_FMAN_SP_DMA_WRITE_OPTIMIZE;
    cfg->no_scather_gather =
            DEFAULT_FMAN_SP_NO_SCATTER_GATHER;
}