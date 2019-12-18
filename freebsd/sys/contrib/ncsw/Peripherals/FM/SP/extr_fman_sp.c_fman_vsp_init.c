#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct fman_sp_int_context_data_copy {scalar_t__ size; scalar_t__ int_context_offset; scalar_t__ ext_buf_offset; } ;
struct fman_sp_buf_margins {scalar_t__ end_margins; scalar_t__ start_margins; } ;
struct fman_ext_pools {int num_pools_used; TYPE_1__* ext_buf_pool; } ;
struct fman_buf_pool_depletion {scalar_t__* pfc_priorities_en; scalar_t__ buf_pool_depletion_enabled; int /*<<< orphan*/  pools_to_consider_for_single_mode; scalar_t__ single_pool_mode_enable; scalar_t__ num_pools; int /*<<< orphan*/  pools_to_consider; scalar_t__ pools_grp_mode_enable; } ;
struct fman_backup_bm_pools {int num_backup_pools; scalar_t__* pool_ids; } ;
struct fm_storage_profile_params {int no_scather_gather; size_t liodn_offset; scalar_t__ dma_write_optimize; scalar_t__ scatter_gather_cache_attr; scalar_t__ header_cache_attr; scalar_t__ int_context_cache_attr; scalar_t__ dma_swap_data; struct fman_sp_buf_margins* buf_margins; struct fman_sp_int_context_data_copy* int_context; struct fman_backup_bm_pools backup_pools; struct fman_buf_pool_depletion buf_pool_depletion; struct fman_ext_pools fm_ext_pools; } ;
struct fm_pcd_storage_profile_regs {int /*<<< orphan*/  fm_sp_spliodn; int /*<<< orphan*/  fm_sp_ebm; int /*<<< orphan*/  fm_sp_icp; int /*<<< orphan*/  fm_sp_da; int /*<<< orphan*/  fm_sp_mpd; int /*<<< orphan*/ * fm_sp_ebmpi; } ;
struct TYPE_2__ {scalar_t__ id; int size; } ;

/* Variables and functions */
 int FMAN_SP_DMA_ATTR_HDR_CACHE_SHIFT ; 
 int FMAN_SP_DMA_ATTR_IC_CACHE_SHIFT ; 
 int FMAN_SP_DMA_ATTR_SG_CACHE_SHIFT ; 
 int FMAN_SP_DMA_ATTR_SWP_SHIFT ; 
 int FMAN_SP_DMA_ATTR_WRITE_OPTIMIZE ; 
 int FMAN_SP_EXT_BUF_MARG_END_SHIFT ; 
 int FMAN_SP_EXT_BUF_MARG_START_SHIFT ; 
 int FMAN_SP_EXT_BUF_POOL_BACKUP ; 
 int FMAN_SP_EXT_BUF_POOL_EN_COUNTER ; 
 int FMAN_SP_EXT_BUF_POOL_ID_SHIFT ; 
 int FMAN_SP_EXT_BUF_POOL_VALID ; 
 int FMAN_SP_IC_FROM_INT_SHIFT ; 
 int FMAN_SP_IC_SIZE_SHIFT ; 
 int FMAN_SP_IC_TO_EXT_SHIFT ; 
 int FMAN_SP_POOL_DEP_NUM_OF_POOLS_SHIFT ; 
 int FMAN_SP_SG_DISABLE ; 
 int OFFSET_UNITS ; 
 scalar_t__ TRUE ; 
 int calc_vec_dep (int,int /*<<< orphan*/ ,struct fman_ext_pools*,int) ; 
 int /*<<< orphan*/  iowrite32be (size_t,int /*<<< orphan*/ *) ; 

void fman_vsp_init(struct fm_pcd_storage_profile_regs   *regs,
    uint16_t index, struct fm_storage_profile_params *fm_vsp_params,
    int port_max_num_of_ext_pools, int bm_max_num_of_pools,
    int max_num_of_pfc_priorities)
{
    int i = 0, j = 0;
    struct fm_pcd_storage_profile_regs *sp_regs;
    uint32_t tmp_reg, vector;
    struct fman_ext_pools *ext_buf_pools = &fm_vsp_params->fm_ext_pools;
    struct fman_buf_pool_depletion *buf_pool_depletion =
                    &fm_vsp_params->buf_pool_depletion;
    struct fman_backup_bm_pools *backup_pools =
                    &fm_vsp_params->backup_pools;
    struct fman_sp_int_context_data_copy *int_context_data_copy =
                        fm_vsp_params->int_context;
    struct fman_sp_buf_margins *external_buffer_margins =
                        fm_vsp_params->buf_margins;
    bool no_scather_gather = fm_vsp_params->no_scather_gather;
    uint16_t liodn_offset = fm_vsp_params->liodn_offset;

    sp_regs = &regs[index];

    /* fill external buffers manager pool information register*/
    for (i = 0; i < ext_buf_pools->num_pools_used; i++) {
        tmp_reg = FMAN_SP_EXT_BUF_POOL_VALID |
            FMAN_SP_EXT_BUF_POOL_EN_COUNTER;
        tmp_reg |= ((uint32_t)ext_buf_pools->ext_buf_pool[i].id <<
            FMAN_SP_EXT_BUF_POOL_ID_SHIFT);
        tmp_reg |= ext_buf_pools->ext_buf_pool[i].size;
        /* functionality available only for some deriviatives
             (limited by config) */
        for (j = 0; j < backup_pools->num_backup_pools; j++)
            if (ext_buf_pools->ext_buf_pool[i].id ==
                backup_pools->pool_ids[j]) {
                tmp_reg |= FMAN_SP_EXT_BUF_POOL_BACKUP;
                break;
            }
        iowrite32be(tmp_reg, &sp_regs->fm_sp_ebmpi[i]);
    }

    /* clear unused pools */
    for (i = ext_buf_pools->num_pools_used;
        i < port_max_num_of_ext_pools; i++)
        iowrite32be(0, &sp_regs->fm_sp_ebmpi[i]);

    /* fill pool depletion register*/
    tmp_reg = 0;
    if (buf_pool_depletion->buf_pool_depletion_enabled && buf_pool_depletion->pools_grp_mode_enable) {
        /* calculate vector for number of pools depletion */
        vector = calc_vec_dep(bm_max_num_of_pools, buf_pool_depletion->
                pools_to_consider, ext_buf_pools, 0x80000000);

        /* configure num of pools and vector for number of pools mode */
        tmp_reg |= (((uint32_t)buf_pool_depletion->num_pools - 1) <<
            FMAN_SP_POOL_DEP_NUM_OF_POOLS_SHIFT);
        tmp_reg |= vector;
    }

    if (buf_pool_depletion->buf_pool_depletion_enabled && buf_pool_depletion->single_pool_mode_enable) {
        /* calculate vector for number of pools depletion */
        vector = calc_vec_dep(bm_max_num_of_pools, buf_pool_depletion->
                pools_to_consider_for_single_mode,
                ext_buf_pools, 0x00000080);

        /* configure num of pools and vector for number of pools mode */
        tmp_reg |= vector;
    }

    /* fill QbbPEV */
    if (buf_pool_depletion->buf_pool_depletion_enabled) {
        vector = 0;
        for (i = 0; i < max_num_of_pfc_priorities; i++)
            if (buf_pool_depletion->pfc_priorities_en[i] == TRUE)
                vector |= 0x00000100 << i;
        tmp_reg |= vector;
    }
    iowrite32be(tmp_reg, &sp_regs->fm_sp_mpd);

    /* fill dma attributes register */
    tmp_reg = 0;
    tmp_reg |= (uint32_t)fm_vsp_params->dma_swap_data <<
        FMAN_SP_DMA_ATTR_SWP_SHIFT;
    tmp_reg |= (uint32_t)fm_vsp_params->int_context_cache_attr <<
        FMAN_SP_DMA_ATTR_IC_CACHE_SHIFT;
    tmp_reg |= (uint32_t)fm_vsp_params->header_cache_attr <<
        FMAN_SP_DMA_ATTR_HDR_CACHE_SHIFT;
    tmp_reg |= (uint32_t)fm_vsp_params->scatter_gather_cache_attr <<
        FMAN_SP_DMA_ATTR_SG_CACHE_SHIFT;
    if (fm_vsp_params->dma_write_optimize)
        tmp_reg |= FMAN_SP_DMA_ATTR_WRITE_OPTIMIZE;
    iowrite32be(tmp_reg, &sp_regs->fm_sp_da);

    /* IC parameters - fill internal context parameters register */
    tmp_reg = 0;
    tmp_reg |= (((uint32_t)int_context_data_copy->ext_buf_offset/
        OFFSET_UNITS) << FMAN_SP_IC_TO_EXT_SHIFT);
    tmp_reg |= (((uint32_t)int_context_data_copy->int_context_offset/
        OFFSET_UNITS) << FMAN_SP_IC_FROM_INT_SHIFT);
    tmp_reg |= (((uint32_t)int_context_data_copy->size/OFFSET_UNITS) <<
        FMAN_SP_IC_SIZE_SHIFT);
    iowrite32be(tmp_reg, &sp_regs->fm_sp_icp);

    /* buffer margins - fill external buffer margins register */
    tmp_reg = 0;
    tmp_reg |= (((uint32_t)external_buffer_margins->start_margins) <<
        FMAN_SP_EXT_BUF_MARG_START_SHIFT);
    tmp_reg |= (((uint32_t)external_buffer_margins->end_margins) <<
        FMAN_SP_EXT_BUF_MARG_END_SHIFT);
    if (no_scather_gather)
        tmp_reg |= FMAN_SP_SG_DISABLE;
    iowrite32be(tmp_reg, &sp_regs->fm_sp_ebm);

    /* buffer margins - fill spliodn register */
    iowrite32be(liodn_offset, &sp_regs->fm_sp_spliodn);
}