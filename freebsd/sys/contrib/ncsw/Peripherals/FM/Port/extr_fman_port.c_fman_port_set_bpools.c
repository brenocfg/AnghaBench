#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct fman_port_bpools {int count; scalar_t__ grp_bp_depleted_num; TYPE_4__* bpool; scalar_t__ counters_enable; } ;
struct fman_port {int type; int ext_pools_num; int fm_rev_maj; TYPE_3__* bmi_regs; } ;
struct TYPE_8__ {scalar_t__ size; scalar_t__ pfc_priorities_en; scalar_t__ single_bp_depleted; scalar_t__ grp_bp_depleted; scalar_t__ is_backup; scalar_t__ bpid; } ;
struct TYPE_6__ {int* fmbm_oebmpi; int fmbm_ompd; } ;
struct TYPE_5__ {int* fmbm_ebmpi; int fmbm_mpd; } ;
struct TYPE_7__ {TYPE_2__ oh; TYPE_1__ rx; } ;

/* Variables and functions */
 int BMI_EXT_BUF_POOL_BACKUP ; 
 int BMI_EXT_BUF_POOL_EN_COUNTER ; 
 int BMI_EXT_BUF_POOL_ID_MASK ; 
 int BMI_EXT_BUF_POOL_ID_SHIFT ; 
 int BMI_EXT_BUF_POOL_VALID ; 
 int BMI_POOL_DEP_NUM_OF_POOLS_SHIFT ; 
 int EINVAL ; 
#define  E_FMAN_PORT_TYPE_OP 130 
#define  E_FMAN_PORT_TYPE_RX 129 
#define  E_FMAN_PORT_TYPE_RX_10G 128 
 int FALSE ; 
 int FMAN_PORT_MAX_EXT_POOLS_NUM ; 
 int FMAN_PORT_OBS_EXT_POOLS_NUM ; 
 int TRUE ; 
 int /*<<< orphan*/  iowrite32be (int,int*) ; 

int fman_port_set_bpools(const struct fman_port *port,
        const struct fman_port_bpools *bp)
{
    uint32_t tmp, *bp_reg, *bp_depl_reg;
    uint8_t i, max_bp_num;
    bool grp_depl_used = FALSE, rx_port;

    switch (port->type) {
    case E_FMAN_PORT_TYPE_RX:
    case E_FMAN_PORT_TYPE_RX_10G:
        max_bp_num = port->ext_pools_num;
        rx_port = TRUE;
        bp_reg = port->bmi_regs->rx.fmbm_ebmpi;
        bp_depl_reg = &port->bmi_regs->rx.fmbm_mpd;
        break;
    case E_FMAN_PORT_TYPE_OP:
        if (port->fm_rev_maj != 4)
            return -EINVAL;
        max_bp_num = FMAN_PORT_OBS_EXT_POOLS_NUM;
        rx_port = FALSE;
        bp_reg = port->bmi_regs->oh.fmbm_oebmpi;
        bp_depl_reg = &port->bmi_regs->oh.fmbm_ompd;
        break;
    default:
        return -EINVAL;
    }

    if (rx_port) {
        /* Check buffers are provided in ascending order */
        for (i = 0;
             (i < (bp->count-1) && (i < FMAN_PORT_MAX_EXT_POOLS_NUM - 1));
             i++) {
            if (bp->bpool[i].size > bp->bpool[i+1].size)
                return -EINVAL;
        }
    }

    /* Set up external buffers pools */
    for (i = 0; i < bp->count; i++) {
        tmp = BMI_EXT_BUF_POOL_VALID;
        tmp |= ((uint32_t)bp->bpool[i].bpid <<
            BMI_EXT_BUF_POOL_ID_SHIFT) & BMI_EXT_BUF_POOL_ID_MASK;

        if (rx_port) {
            if (bp->counters_enable)
                tmp |= BMI_EXT_BUF_POOL_EN_COUNTER;

            if (bp->bpool[i].is_backup)
                tmp |= BMI_EXT_BUF_POOL_BACKUP;

            tmp |= (uint32_t)bp->bpool[i].size;
        }

        iowrite32be(tmp, &bp_reg[i]);
    }

    /* Clear unused pools */
    for (i = bp->count; i < max_bp_num; i++)
        iowrite32be(0, &bp_reg[i]);

    /* Pools depletion */
    tmp = 0;
    for (i = 0; i < FMAN_PORT_MAX_EXT_POOLS_NUM; i++) {
        if (bp->bpool[i].grp_bp_depleted) {
            grp_depl_used = TRUE;
            tmp |= 0x80000000 >> i;
        }

        if (bp->bpool[i].single_bp_depleted)
            tmp |= 0x80 >> i;

        if (bp->bpool[i].pfc_priorities_en)
            tmp |= 0x0100 << i;
    }

    if (grp_depl_used)
        tmp |= ((uint32_t)bp->grp_bp_depleted_num - 1) <<
            BMI_POOL_DEP_NUM_OF_POOLS_SHIFT;

    iowrite32be(tmp, bp_depl_reg);
    return 0;
}