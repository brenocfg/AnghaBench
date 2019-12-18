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
struct fman_port_cfg {int rx_cut_end_bytes; int rx_pri_elevation; int rx_fifo_thr; int tx_fifo_low_comf_level; int tx_fifo_deq_pipeline_depth; int deq_byte_cnt; int /*<<< orphan*/  no_scatter_gather; void* deq_high_pri; int /*<<< orphan*/  deq_prefetch_opt; void* sync_req; int /*<<< orphan*/  deq_type; void* perf_counters_enable; void* stats_counters_enable; scalar_t__ tx_fifo_min_level; scalar_t__ ext_buf_end_margin; scalar_t__ ext_buf_start_margin; scalar_t__ int_buf_start_margin; scalar_t__ ic_size; scalar_t__ ic_int_offset; scalar_t__ ic_ext_offset; scalar_t__ rx_fd_bits; scalar_t__ checksum_bytes_ignore; void* discard_override; int /*<<< orphan*/  color; void* dma_write_optimize; void* dma_sg_stash_on; void* dma_header_stash_on; void* dma_ic_stash_on; int /*<<< orphan*/  dma_swap_data; } ;
typedef  enum fman_port_type { ____Placeholder_fman_port_type } fman_port_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FMAN_SP_NO_SCATTER_GATHER ; 
 int /*<<< orphan*/  E_FMAN_PORT_COLOR_GREEN ; 
 int /*<<< orphan*/  E_FMAN_PORT_DEQ_BY_PRI ; 
 int /*<<< orphan*/  E_FMAN_PORT_DEQ_FULL_PREFETCH ; 
 int /*<<< orphan*/  E_FMAN_PORT_DEQ_NO_PREFETCH ; 
 int /*<<< orphan*/  E_FMAN_PORT_DMA_NO_SWAP ; 
 int E_FMAN_PORT_TYPE_HC ; 
 int E_FMAN_PORT_TYPE_OP ; 
 int E_FMAN_PORT_TYPE_TX_10G ; 
 void* FALSE ; 
 int FMAN_PORT_BMI_FIFO_UNITS ; 
 int KILOBYTE ; 
 void* TRUE ; 

void fman_port_defconfig(struct fman_port_cfg *cfg, enum fman_port_type type)
{
    cfg->dma_swap_data = E_FMAN_PORT_DMA_NO_SWAP;
    cfg->dma_ic_stash_on = FALSE;
    cfg->dma_header_stash_on = FALSE;
    cfg->dma_sg_stash_on = FALSE;
    cfg->dma_write_optimize = TRUE;
    cfg->color = E_FMAN_PORT_COLOR_GREEN;
    cfg->discard_override = FALSE;
    cfg->checksum_bytes_ignore = 0;
    cfg->rx_cut_end_bytes = 4;
    cfg->rx_pri_elevation = ((0x3FF + 1) * FMAN_PORT_BMI_FIFO_UNITS);
    cfg->rx_fifo_thr = ((0x3FF + 1) * FMAN_PORT_BMI_FIFO_UNITS);
    cfg->rx_fd_bits = 0;
    cfg->ic_ext_offset = 0;
    cfg->ic_int_offset = 0;
    cfg->ic_size = 0;
    cfg->int_buf_start_margin = 0;
    cfg->ext_buf_start_margin = 0;
    cfg->ext_buf_end_margin = 0;
    cfg->tx_fifo_min_level  = 0;
    cfg->tx_fifo_low_comf_level = (5 * KILOBYTE);
    cfg->stats_counters_enable = TRUE;
    cfg->perf_counters_enable = TRUE;
    cfg->deq_type = E_FMAN_PORT_DEQ_BY_PRI;

    if (type == E_FMAN_PORT_TYPE_HC) {
        cfg->sync_req = FALSE;
        cfg->deq_prefetch_opt = E_FMAN_PORT_DEQ_NO_PREFETCH;
    } else {
        cfg->sync_req = TRUE;
        cfg->deq_prefetch_opt = E_FMAN_PORT_DEQ_FULL_PREFETCH;
    }

    if (type == E_FMAN_PORT_TYPE_TX_10G) {
        cfg->tx_fifo_deq_pipeline_depth = 4;
        cfg->deq_high_pri = TRUE;
        cfg->deq_byte_cnt = 0x1400;
    } else {
        if ((type == E_FMAN_PORT_TYPE_HC) ||
                (type == E_FMAN_PORT_TYPE_OP))
            cfg->tx_fifo_deq_pipeline_depth = 2;
        else
            cfg->tx_fifo_deq_pipeline_depth = 1;

        cfg->deq_high_pri = FALSE;
        cfg->deq_byte_cnt = 0x400;
    }
    cfg->no_scatter_gather = DEFAULT_FMAN_SP_NO_SCATTER_GATHER;
}