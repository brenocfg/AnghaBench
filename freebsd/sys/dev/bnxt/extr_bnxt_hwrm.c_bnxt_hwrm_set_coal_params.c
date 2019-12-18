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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct hwrm_ring_cmpl_ring_cfg_aggint_params_input {void* num_cmpl_aggr_int; void* int_lat_tmr_max; void* int_lat_tmr_min; void* cmpl_aggr_dma_tmr_during_int; void* cmpl_aggr_dma_tmr; void* num_cmpl_dma_aggr_during_int; void* num_cmpl_dma_aggr; void* flags; } ;
struct bnxt_softc {int dummy; } ;

/* Variables and functions */
 void* htole16 (int) ; 

__attribute__((used)) static void bnxt_hwrm_set_coal_params(struct bnxt_softc *softc, uint32_t max_frames,
        uint32_t buf_tmrs, uint16_t flags,
        struct hwrm_ring_cmpl_ring_cfg_aggint_params_input *req)
{
        req->flags = htole16(flags);
        req->num_cmpl_dma_aggr = htole16((uint16_t)max_frames);
        req->num_cmpl_dma_aggr_during_int = htole16(max_frames >> 16);
        req->cmpl_aggr_dma_tmr = htole16((uint16_t)buf_tmrs);
        req->cmpl_aggr_dma_tmr_during_int = htole16(buf_tmrs >> 16);
        /* Minimum time between 2 interrupts set to buf_tmr x 2 */
        req->int_lat_tmr_min = htole16((uint16_t)buf_tmrs * 2);
        req->int_lat_tmr_max = htole16((uint16_t)buf_tmrs * 4);
        req->num_cmpl_aggr_int = htole16((uint16_t)max_frames * 4);
}