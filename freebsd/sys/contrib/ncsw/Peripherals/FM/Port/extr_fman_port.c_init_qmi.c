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
struct fman_port_qmi_regs {int /*<<< orphan*/  fmqm_pndc; int /*<<< orphan*/  fmqm_pndn; int /*<<< orphan*/  fmqm_pnen; int /*<<< orphan*/  fmqm_pnc; } ;
struct fman_port_params {int deq_sp; } ;
struct fman_port_cfg {int deq_type; int deq_prefetch_opt; int deq_byte_cnt; scalar_t__ qmi_deq_options_support; scalar_t__ deq_high_pri; scalar_t__ queue_counters_enable; } ;
struct fman_port {scalar_t__ type; struct fman_port_qmi_regs* qmi_regs; } ;

/* Variables and functions */
 int EINVAL ; 
#define  E_FMAN_PORT_DEQ_ACTIVE_FQ 133 
#define  E_FMAN_PORT_DEQ_ACTIVE_FQ_NO_ICS 132 
#define  E_FMAN_PORT_DEQ_BY_PRI 131 
#define  E_FMAN_PORT_DEQ_FULL_PREFETCH 130 
#define  E_FMAN_PORT_DEQ_NO_PREFETCH 129 
#define  E_FMAN_PORT_DEQ_PART_PREFETCH 128 
 scalar_t__ E_FMAN_PORT_TYPE_HC ; 
 scalar_t__ E_FMAN_PORT_TYPE_RX ; 
 scalar_t__ E_FMAN_PORT_TYPE_RX_10G ; 
 scalar_t__ E_FMAN_PORT_TYPE_TX ; 
 scalar_t__ E_FMAN_PORT_TYPE_TX_10G ; 
 int NIA_BMI_AC_FETCH ; 
 int NIA_BMI_AC_RELEASE ; 
 int NIA_BMI_AC_TX ; 
 int NIA_BMI_AC_TX_RELEASE ; 
 int NIA_ENG_BMI ; 
 int QMI_DEQ_CFG_PREFETCH_FULL ; 
 int QMI_DEQ_CFG_PREFETCH_PARTIAL ; 
 int QMI_DEQ_CFG_PRI ; 
 int QMI_DEQ_CFG_SP_MASK ; 
 int QMI_DEQ_CFG_SP_SHIFT ; 
 int QMI_DEQ_CFG_TYPE1 ; 
 int QMI_DEQ_CFG_TYPE2 ; 
 int QMI_DEQ_CFG_TYPE3 ; 
 int QMI_PORT_CFG_EN_COUNTERS ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_qmi(struct fman_port *port,
        struct fman_port_cfg *cfg,
        struct fman_port_params *params)
{
    struct fman_port_qmi_regs *regs = port->qmi_regs;
    uint32_t tmp;

    tmp = 0;
    if (cfg->queue_counters_enable)
        tmp |= QMI_PORT_CFG_EN_COUNTERS;
    iowrite32be(tmp, &regs->fmqm_pnc);

    /* Rx port configuration */
    if ((port->type == E_FMAN_PORT_TYPE_RX) ||
            (port->type == E_FMAN_PORT_TYPE_RX_10G)) {
        /* Enqueue NIA */
        iowrite32be(NIA_ENG_BMI | NIA_BMI_AC_RELEASE, &regs->fmqm_pnen);
        return 0;
    }

    /* Continue with Tx and O/H port configuration */
    if ((port->type == E_FMAN_PORT_TYPE_TX) ||
            (port->type == E_FMAN_PORT_TYPE_TX_10G)) {
        /* Enqueue NIA */
        iowrite32be(NIA_ENG_BMI | NIA_BMI_AC_TX_RELEASE,
                &regs->fmqm_pnen);
        /* Dequeue NIA */
        iowrite32be(NIA_ENG_BMI | NIA_BMI_AC_TX, &regs->fmqm_pndn);
    } else {
        /* Enqueue NIA */
        iowrite32be(NIA_ENG_BMI | NIA_BMI_AC_RELEASE, &regs->fmqm_pnen);
        /* Dequeue NIA */
        iowrite32be(NIA_ENG_BMI | NIA_BMI_AC_FETCH, &regs->fmqm_pndn);
    }

    /* Dequeue Configuration register */
    tmp = 0;
    if (cfg->deq_high_pri)
        tmp |= QMI_DEQ_CFG_PRI;

    switch (cfg->deq_type) {
    case E_FMAN_PORT_DEQ_BY_PRI:
        tmp |= QMI_DEQ_CFG_TYPE1;
        break;
    case E_FMAN_PORT_DEQ_ACTIVE_FQ:
        tmp |= QMI_DEQ_CFG_TYPE2;
        break;
    case E_FMAN_PORT_DEQ_ACTIVE_FQ_NO_ICS:
        tmp |= QMI_DEQ_CFG_TYPE3;
        break;
    default:
        return -EINVAL;
    }

    if (cfg->qmi_deq_options_support) {
        if ((port->type == E_FMAN_PORT_TYPE_HC) &&
            (cfg->deq_prefetch_opt != E_FMAN_PORT_DEQ_NO_PREFETCH))
            return -EINVAL;

        switch (cfg->deq_prefetch_opt) {
        case E_FMAN_PORT_DEQ_NO_PREFETCH:
            break;
        case E_FMAN_PORT_DEQ_PART_PREFETCH:
            tmp |= QMI_DEQ_CFG_PREFETCH_PARTIAL;
            break;
        case E_FMAN_PORT_DEQ_FULL_PREFETCH:
            tmp |= QMI_DEQ_CFG_PREFETCH_FULL;
            break;
        default:
            return -EINVAL;
        }
    }
    tmp |= (uint32_t)(params->deq_sp & QMI_DEQ_CFG_SP_MASK) <<
            QMI_DEQ_CFG_SP_SHIFT;
    tmp |= cfg->deq_byte_cnt;
    iowrite32be(tmp, &regs->fmqm_pndc);

    return 0;
}